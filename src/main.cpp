#include <iostream>
#include "logic.hpp"
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <signal.h>
#include <libunwind.h>
#include <iostream>
#include <string.h>
#include <sys/prctl.h>
#include <execinfo.h>
#define UNW_LOCAL_ONLY

#define always_inline __attribute__((always_inline))
#define no_inline     __attribute__((noinline))

no_inline static void libunwind_backtrace(void)
{
    int32_t       ret, count, len, max_len;
    unw_cursor_t  cursor;
    unw_context_t context;
    unw_word_t    offset, pc, sp;
    Dl_info       dl_info;
    const char   *dname;
    char          fname[256], comm_name[32];
    char          buffer[4096];

    /* Initialize cursor to current frame for local unwinding. */
    if (unw_getcontext(&context) != 0) {
        printf("unw_getcontext error.\n");
        return;
    }
    if (unw_init_local(&cursor, &context) != 0) {
        printf("unw_init_local error.\n");
        return;
    }

    /* 获取当前线程名字, 通过prctl */
    memset(comm_name, 0, sizeof(comm_name));
    if (prctl(PR_GET_NAME, comm_name) != 0) {
        printf("prctl error : %s(%d).\n", strerror(errno), errno);
        snprintf(comm_name, sizeof(comm_name), "(unknown)");
    }

    len     = 0;
    max_len = sizeof(buffer);
    count   = 0;
    len += snprintf(buffer, (size_t)max_len, "Stack trace for [%s]:\n", comm_name);
    // Unwind frames one by one, going up the frame stack.
    while (unw_step(&cursor) > 0) {
        if (unw_get_reg(&cursor, UNW_REG_IP, &pc) != 0) {
            printf("unw_get_reg error.\n");
            return;
        }
        /* 获取栈指针SP的值 */
        if (unw_get_reg(&cursor, UNW_REG_SP, &sp) != 0) {
            printf("unw_get_reg error.\n");
            return;
        };

        ret = unw_get_proc_name(&cursor, fname, sizeof(fname), &offset);
        if (ret != 0) {
            snprintf(fname, sizeof(fname), "??????");
            offset = 0;
        }

        /* 获取符号所属二进制文件名 */
        if (dladdr((void *)pc, &dl_info) && dl_info.dli_fname) {
            dname = dl_info.dli_fname;
        } else {
            dname = "(unknown)";
        }

        len += snprintf(buffer + len, (size_t)(max_len - len),
            "[%2d]-> PC 0x%-12lx, SP 0x%-12lx: [%s](+0x%lx) from [%s]\n", count++, pc, sp, fname,
            offset, dname);
        if (len >= max_len - 1) {
            break;
        }
    }

    buffer[sizeof(buffer) - 1] = '\0'; /* Ensure null termination. */
    printf("%s", buffer);

    return;
}

void exitHandler(int sgn)
{
    std::cout << "signl:" << sgn << std::endl;
    libunwind_backtrace();
    exit(0);
}

int main()
{
    //Ctrl+C
    signal(SIGINT, exitHandler);
    //abort发出的信号
    signal(SIGABRT, exitHandler);
    //非法内存访问	
    signal(SIGBUS, exitHandler);
    //kill信号	
    signal(SIGKILL, exitHandler);
    //无效内存访问
    signal(SIGSEGV, exitHandler);
    //栈溢出	
    signal(SIGSTKFLT, exitHandler);
    //进程停止	
    signal(SIGSTOP, exitHandler);
    logic lg;
    lg.init_dds();
    // while (!lg.start())
    // {
    //     sleep(1);
    // }
    // while (1)
    // {
    //     //lg.call();
    //     //sleep(1);
    //     usleep(1* 10);
    //     lg.Publish();
    // }

    //lg.Publish();
    
    return 0;
}
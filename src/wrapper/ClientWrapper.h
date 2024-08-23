#pragma once
#include "ClientBase.h"
#include <mutex>
#include "../log_define.h"

namespace wk {
    class ClientWrapper
    {
    private:
        const std::string client_name_ = "/tcl2indemind";
        static std::atomic_bool is_init_;
        static ClientBase *client_;
        std::string topic_;
        static std::mutex mtx;
    public:
        ClientWrapper()= default;
        ~ClientWrapper();
        bool init(std::string name);
        bool request(const std::string& req,std::string& resp);
        static void cleanup();
    };
}
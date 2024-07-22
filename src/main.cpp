#include <iostream>
#include "logic.hpp"
#include <unistd.h>

int main()
{
    logic lg;
    lg.init_dds();
    // while (!lg.start())
    // {
    //     /* code */
    // }
    lg.call();
    while (1)
    {
        sleep(1);
    }
    
    return 0;
}
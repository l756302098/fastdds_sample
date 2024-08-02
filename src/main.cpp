#include <iostream>
#include "logic.hpp"
#include <unistd.h>

int main()
{
    logic lg;
    lg.init_dds();
    // while (!lg.start())
    // {
    //     sleep(1);
    // }
    while (1)
    {
        //lg.call();
        sleep(1);
        lg.Publish();
    }
    
    return 0;
}
#pragma once
#include "../../json.hpp"

class JReportRoboticState
{
public:
    std::int64_t time = 0;
    int state = 0;


    JReportRoboticState() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["time"] = time;
        msg["state"] = state;

        return msg.dump();
    }
};
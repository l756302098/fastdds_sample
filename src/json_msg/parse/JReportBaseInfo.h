#pragma once
#include "../../json.hpp"

class JReportBaseInfo
{
public:
    std::int64_t time = 0;
    float barrery = 0.0;


    JReportBaseInfo() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["time"] = time;
        msg["barrery"] = barrery;

        return msg.dump();
    }
};

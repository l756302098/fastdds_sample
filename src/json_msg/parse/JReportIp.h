#pragma once
#include "../../json.hpp"

class JReportIp
{
public:
    std::int64_t time = 0;
    std::string ip,ssid;


    JReportIp() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["time"] = time;
        msg["ip"] = ip;
        msg["ssid"] = ssid;

        return msg.dump();
    }
};

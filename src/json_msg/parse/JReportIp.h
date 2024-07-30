#pragma once
#include "../../json.hpp"

class JReportIp
{
public:
    std::int64_t time = 0;
    std::string ip,ssid;
    bool parsed;


    JReportIp() = default;

    JReportIp(const std::string& data)
    {
        nlohmann::json msg = nlohmann::json::parse(data);
        if (msg.contains("time") && msg["time"].is_number())
        {
            time = msg["time"].get<std::int64_t>();
        }
        else
        {
            this->parsed = false;
        }

        if (msg.contains("ip") && msg["ip"].is_number())
        {
            ip = msg["ip"].get<std::string>();
        }
        else
        {
            this->parsed = false;
        } 

        if (msg.contains("ssid") && msg["ssid"].is_number())
        {
            ssid = msg["ssid"].get<float>();
        }
        else
        {
            this->parsed = false;
        }
    }
    
    std::string toString()
    {
        json msg = json::object();
        msg["time"] = time;
        msg["ip"] = ip;
        msg["ssid"] = ssid;

        return msg.dump();
    }
};

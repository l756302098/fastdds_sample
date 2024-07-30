#pragma once
#include "../../json.hpp"

class JReportBaseInfo
{
public:
    std::int64_t time = 0;
    float barrery = 0.0;
    bool parsed;

    JReportBaseInfo() = default;
    JReportBaseInfo(const std::string& data)
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

        if (msg.contains("battery_level") && msg["battery_level"].is_number())
        {
            barrery = msg["battery_level"].get<float>();
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
        msg["battery_level"] = barrery;

        return msg.dump();
    }
};

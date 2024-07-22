#pragma once
#include "../../json.hpp"

class JReportPose
{
public:
    std::int64_t time = 0;
    float x,y,angle;
    bool parsed;

    JReportPose() = delete;

    JReportPose(const std::string& data)
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

        if (msg.contains("x") && msg["x"].is_number())
        {
            x = msg["x"].get<float>();
        }
        else
        {
            this->parsed = false;
        } 

        if (msg.contains("y") && msg["y"].is_number())
        {
            y = msg["y"].get<float>();
        }
        else
        {
            this->parsed = false;
        } 

        if (msg.contains("angle") && msg["angle"].is_number())
        {
            angle = msg["angle"].get<float>();
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
        msg["x"] = x;
        msg["y"] = y;
        msg["angle"] = angle;

        return msg.dump();
    }
};
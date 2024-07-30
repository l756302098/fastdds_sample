#pragma once
#include "../../json.hpp"

class JReportTaskState
{
public:
    std::int64_t time = 0;
    int state = 0;
    std::string task_uuid;
    bool parsed;

    JReportTaskState() = default;
    JReportTaskState(const std::string& data)
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

        if (msg.contains("task_uuid") && msg["task_uuid"].is_number())
        {
            task_uuid = msg["task_uuid"].get<std::string>();
        }
        else
        {
            this->parsed = false;
        } 

        if (msg.contains("state") && msg["state"].is_number())
        {
            state = msg["state"].get<int>();
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
        msg["task_uuid"] = task_uuid;
        msg["state"] = state;

        return msg.dump();
    }
};
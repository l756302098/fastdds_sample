#pragma once
#include "../../json.hpp"

class JReportTaskState
{
public:
    std::int64_t time = 0;
    int state = 0;
    std::string task_uuid;

    JReportTaskState() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["time"] = time;
        msg["task_uuid"] = task_uuid;
        msg["state"] = state;

        return msg.dump();
    }
};
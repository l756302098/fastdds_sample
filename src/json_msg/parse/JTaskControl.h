#pragma once
#include "../../json.hpp"


using json = nlohmann::json;

class JTaskControlRequest
{
private:
    bool parsed = true;

public:
    std::int64_t time;
    std::string uuid;
    int type;


    JTaskControlRequest() = delete;
    JTaskControlRequest(const std::string& data)
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

        if (msg.contains("operation_type") && msg["operation_type"].is_number())
        {
            type = msg["operation_type"].get<int>();
        }
        else
        {
            this->parsed = false;
        }

        if (msg.contains("task_uuid") && msg["task_uuid"].is_string())
        {
            uuid = msg["task_uuid"].get<std::string>();
        }
        else
        {
            this->parsed = false;
        }
    }

    std::string toString()
    {
        return "";
    }

    bool isSuccess()
    {
        return parsed;
    }
};

class JTaskControlResponse
{
public:
    int code = 0;

    JTaskControlResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;

        return msg.dump();
    }
};


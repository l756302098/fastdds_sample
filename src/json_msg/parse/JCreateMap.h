#pragma once
#include "../../json.hpp"

using json = nlohmann::json;

class JCreateMapRequest
{
private:
    bool parsed = true;

public:
    std::int64_t time = 0;

    JCreateMapRequest() = default;
    JCreateMapRequest(const std::string& data)
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
    }

    std::string toString()
    {
        nlohmann::json msg = nlohmann::json();
        msg["time"] = time;
        return msg.dump();
    }

    bool isSuccess()
    {
        return parsed;
    }
};

class JCreateMapResponse
{
public:
    bool parsed;
    std::string uuid = "";
    int code = 0;

    JCreateMapResponse() = default;
    JCreateMapResponse(const std::string& data)
    {
        nlohmann::json msg = nlohmann::json::parse(data);
        if (msg.contains("code") && msg["code"].is_number())
        {
            code = msg["code"].get<int>();
        }
        else
        {
            this->parsed = false;
        }

        if (msg.contains("uuid") && msg["uuid"].is_string())
        {
            uuid = msg["uuid"].get<std::string>();
        }
        else
        {
            this->parsed = false;
        }
    }
    
    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;
        msg["task_uuid"] = this->uuid;

        return msg.dump();
    }
};


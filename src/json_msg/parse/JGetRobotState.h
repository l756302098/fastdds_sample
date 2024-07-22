#pragma once
#include "../../json.hpp"
#include "../../base64.hpp"

using json = nlohmann::json;

class JGetRobotStateRequest
{
private:
    bool parsed = true;

public:
    std::int64_t time;

    JGetRobotStateRequest() = delete;
    JGetRobotStateRequest(const std::string& data)
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
        return "";
    }

    bool isSuccess()
    {
        return parsed;
    }
};

class JGetRobotStateResponse
{
public:
    int code = 0;
    std::int64_t time;
    int state;

    JGetRobotStateResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;
        msg["time"] = time;
        msg["state"] = state;

        return msg.dump();
    }
};


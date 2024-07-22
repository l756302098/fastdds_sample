#pragma once
#include "../../json.hpp"

using json = nlohmann::json;

class JSerialDataRequest
{
private:
    bool parsed = true;

public:
    std::int64_t time = 0;
    std::string cmd;

    JSerialDataRequest() = delete;
    JSerialDataRequest(const std::string& data)
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

        if (msg.contains("cmd") && msg["cmd"].is_string())
        {
            cmd = msg["cmd"].get<std::string>();
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

class JSerialDataResponse
{
public:
    int code = 0;

    JSerialDataResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;

        return msg.dump();
    }
};


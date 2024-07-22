#pragma once
#include "../../json.hpp"

class JSubCmdVel
{
private:
    bool parsed = true;

public:
    std::int64_t time = 0;
    float linear,angular;

    JSubCmdVel() = delete;
    JSubCmdVel(const std::string& data)
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

        if (msg.contains("linear") && msg["linear"].is_number())
        {
            linear = msg["linear"].get<std::int64_t>();
        }
        else
        {
            this->parsed = false;
        }

        if (msg.contains("angular") && msg["angular"].is_number())
        {
            angular = msg["angular"].get<std::int64_t>();
        }
        else
        {
            this->parsed = false;
        }
    }

    bool isSuccess()
    {
        return parsed;
    }
};

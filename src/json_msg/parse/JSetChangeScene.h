#pragma once
#include "../../json.hpp"

using json = nlohmann::json;

class JSetChangeSceneRequest
{
private:
    bool parsed = true;

public:
    std::int64_t sceneId = 0;

    JSetChangeSceneRequest() = delete;
    JSetChangeSceneRequest(const std::string& data)
    {
        nlohmann::json msg = nlohmann::json::parse(data);
        if (msg.contains("scene_id") && msg["scene_id"].is_number())
        {
            sceneId = msg["scene_id"].get<std::int64_t>();
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

class JSetChangeSceneResponse
{
public:
    int code = 0;

    JSetChangeSceneResponse() = default;

    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;

        return msg.dump();
    }
};

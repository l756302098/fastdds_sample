#pragma once
#include "../../json.hpp"

using json = nlohmann::json;

class JSetManualRequest
{
private:
    bool parsed = true;

public:
    std::int64_t time = 0;
    std::int64_t sceneId,mapId;
    bool flag;

    JSetManualRequest() = delete;
    JSetManualRequest(const std::string& data)
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

        if (msg.contains("flag") && msg["flag"].is_boolean())
        {
            flag = msg["flag"].get<bool>();
        }
        else
        {
            this->parsed = false;
        } 

        if (msg.contains("scene_id") && msg["scene_id"].is_number())
        {
            sceneId = msg["scene_id"].get<std::int64_t>();
        }
        else
        {
            this->parsed = false;
        } 

        if (msg.contains("map_id") && msg["map_id"].is_number())
        {
            mapId = msg["map_id"].get<std::int64_t>();
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

class JSetManualResponse
{
public:
    std::string uuid = "";
    int code = 0;

    JSetManualResponse() = default;

    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;
        msg["task_uuid"] = this->uuid;

        return msg.dump();
    }
};

#pragma once
#include "../../json.hpp"


using json = nlohmann::json;

class JTaskFollowRequest
{
private:
    bool parsed = true;

public:
    std::int64_t time;
    std::int64_t scene_id,map_id;
    float angle;


    JTaskFollowRequest() = delete;
    JTaskFollowRequest(const std::string& data)
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

        if (msg.contains("scene_id") && msg["scene_id"].is_number())
        {
            scene_id = msg["scene_id"].get<std::int64_t>();
        }
        else
        {
            this->parsed = false;
        }

        if (msg.contains("map_id") && msg["map_id"].is_number())
        {
            map_id = msg["map_id"].get<std::int64_t>();
        }
        else
        {
            this->parsed = false;
        }

        if (msg.contains("angle") && msg["angle"].is_number())
        {
            angle = msg["angle"].get<std::int64_t>();
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

class JTaskFollowResponse
{
public:
    int code = 0;
    std::string uuid;

    JTaskFollowResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;
        msg["task_uuid"] = this->uuid;

        return msg.dump();
    }
};


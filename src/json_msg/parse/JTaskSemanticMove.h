#pragma once
#include "../../json.hpp"


using json = nlohmann::json;

class JTaskSemanticMoveRequest
{
private:
    bool parsed = true;

public:
    std::int64_t time;
    std::int64_t scene_id,map_id;
    int item_id,area_id;


    JTaskSemanticMoveRequest() = delete;
    JTaskSemanticMoveRequest(const std::string& data)
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

        if (msg.contains("item_id") && msg["item_id"].is_number())
        {
            item_id = msg["item_id"].get<int>();
        }
        else
        {
            this->parsed = false;
        }

        if (msg.contains("area_id") && msg["area_id"].is_number())
        {
            area_id = msg["area_id"].get<int>();
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

class JTaskSemanticMoveResponse
{
public:
    int code = 0;
    std::string uuid;

    JTaskSemanticMoveResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;
        msg["task_uuid"] = this->uuid;

        return msg.dump();
    }
};


#pragma once
#include "../../json.hpp"

using json = nlohmann::json;

class JGetCurMapIdRequest
{
private:
    bool parsed = true;

public:
    std::int64_t time = 0;

    JGetCurMapIdRequest() = delete;
    JGetCurMapIdRequest(const std::string& data)
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

class JGetCurMapIdResponse
{
public:
    int code = 0;
    std::int64_t sceneId = 0;
    std::int64_t mapId = 0;

    JGetCurMapIdResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;
        msg["scene_id"] = this->sceneId;
        msg["map_id"] = this->mapId;

        return msg.dump();
    }
};


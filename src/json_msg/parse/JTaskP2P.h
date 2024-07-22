#pragma once
#include "../../json.hpp"
#include "CommonMsg.h"

using json = nlohmann::json;

class JTaskP2PRequest
{
private:
    bool parsed = true;

public:
    std::int64_t time;
    std::int64_t scene_id,map_id;
    std::vector<Point2f> pts;


    JTaskP2PRequest() = delete;
    JTaskP2PRequest(const std::string& data)
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

        if (msg.contains("points") && msg["points"].is_array())
        {
            std::map<int,Point2f> ptMap;
            for (const auto &it : msg["points"])
            {
                int num = it["number"].get<std::int64_t>();
                float x = it["x"].get<float>();
                float y = it["y"].get<float>();
                Point2f pt(x,y);
                ptMap.insert(std::make_pair(num,pt));
            }
            
            for (const auto &v : ptMap)
            {
                pts.push_back(v.second);
            }
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

class JTaskP2PResponse
{
public:
    int code = 0;
    std::string uuid;

    JTaskP2PResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;
        msg["task_uuid"] = this->uuid;

        return msg.dump();
    }
};


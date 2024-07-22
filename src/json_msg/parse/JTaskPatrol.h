#pragma once
#include "../../json.hpp"
#include <map>

using json = nlohmann::json;

class JTaskPatrolRequest
{
    struct Point2
    {
        float x;
        float y;
    };
    
private:
    bool parsed = true;

public:
    std::int64_t time;
    std::int64_t scene_id,map_id;
    std::vector<Point2> pts;

    JTaskPatrolRequest() = delete;
    JTaskPatrolRequest(const std::string& data)
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
            int number = -1;
            Point2 pt;
            std::map<int,Point2> mpt;
            for(const auto& it : msg["points"])
            {
                number = it["number"].get<int>();
                pt.x = it["x"].get<float>();
                pt.y = it["y"].get<float>();
                mpt[number] = pt;
            }

            for(auto &item : mpt)
            {
                pts.push_back(item.second);
            }
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

class JTaskPatrolResponse
{
public:
    int code = 0;
    std::string uuid;

    JTaskPatrolResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;
        msg["task_uuid"] = this->uuid;

        return msg.dump();
    }
};


#pragma once
#include "../../json.hpp"
#include <set>

using json = nlohmann::json;

class JSearchPeopleRequest
{
private:
    bool parsed = true;

public:
    std::int64_t time = 0;
    std::int64_t sceneId = 0;
    std::int64_t mapId = 0;
    float priorityAngle = 0;
    std::vector<int> priorityAreas;

    JSearchPeopleRequest() = delete;
    JSearchPeopleRequest(const std::string& data)
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
        if (msg.contains("priority_angle") && msg["priority_angle"].is_number())
        {
            priorityAngle = msg["priority_angle"].get<float>();
        }
        else
        {
            this->parsed = false;
        }
        if (msg.contains("priority_areas") && msg["priority_areas"].is_array())
        {
            int number = -1;
            int id = -1;
            std::map<int, int> tmp; //number && id
            for(auto &obj : msg["priority_areas"])
            {
                if(obj.contains("number") && obj["number"].is_number())
                {
                    number = obj["number"].get<int>();
                }
                if(obj.contains("id") && obj["id"].is_number())
                {
                    id = obj["id"].get<int>();
                }
                if(number != -1 && id != -1)
                {
                    tmp[number] = id;
                }
            }
            for(auto &item : tmp)
            {
                priorityAreas.push_back(item.second);
            }
        }
    }

    bool isSuccess()
    {
        return parsed;
    }
};

class JSearchPeopleResponse
{
public:
    std::string uuid = "";
    int code = 0;

    JSearchPeopleResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;
        msg["task_uuid"] = this->uuid;

        return msg.dump();
    }
};


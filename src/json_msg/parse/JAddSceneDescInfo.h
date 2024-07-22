#pragma once
#include "../../json.hpp"
#include "CommonMsg.h"

using json = nlohmann::json;

class JAddSceneDescInfoRequest
{
private:
    bool parsed = true;

public:
    std::vector<Outline> vOutline;

    JAddSceneDescInfoRequest() = delete;
    JAddSceneDescInfoRequest(const std::string& data)
    {
        nlohmann::json msg = nlohmann::json::parse(data);
        Outline outline;
        if (msg.contains("info") && msg["info"].is_array())
        {
            for (auto it : msg["info"])
            {
                if (it.contains("id") && it["id"].is_number())
                {
                    outline.id = it["id"].get<std::int64_t>();
                }
                else
                {
                    parsed = false;
                }
           
                if (it.contains("scene_id") && it["scene_id"].is_number())
                {
                    outline.sceneId = it["scene_id"].get<std::int64_t>();
                }
                else
                {
                    parsed = false;
                }

                if (it.contains("map_id") && it["map_id"].is_number())
                {
                    outline.mapId = it["map_id"].get<std::int64_t>();
                }
                else
                {
                    parsed = false;
                }

                if (it.contains("type") && it["type"].is_number())
                {
                    outline.outlineType = it["type"].get<std::int64_t>();
                }
                else
                {
                    parsed = false;
                }

                if (it.contains("alias") && it["alias"].is_string())
                {
                    outline.alias = it["alias"].get<std::string>();
                }
                else
                {
                    parsed = false;
                }

                if (it.contains("object_id") && it["object_id"].is_number())
                {
                    outline.objectId = it["object_id"].get<std::int64_t>();
                }
                else
                {
                    parsed = false;
                }

                if (it.contains("class_id") && it["class_id"].is_number())
                {
                    outline.classId = it["class_id"].get<std::int64_t>();
                }
                else
                {
                    parsed = false;
                }

               
                vOutline.push_back(outline);
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

class JAddSceneDescInfoResponse
{
public:
    int code = 0;

    JAddSceneDescInfoResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["code"] = this->code;

        return msg.dump();
    }
};


#pragma once
#include "../../json.hpp"
#include "../../base64.hpp"
#include "CommonMsg.h"

using json = nlohmann::json;

class JGetSceneDescInfoRequest
{
private:
    bool parsed = true;

public:
    std::int64_t sceneId,mapId;

    JGetSceneDescInfoRequest() = delete;
    JGetSceneDescInfoRequest(const std::string& data)
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

class JGetSceneDescInfoResponse
{
public:
    int code = 0;
    std::vector<Outline> outline;

    JGetSceneDescInfoResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        json joutlines = json::array();
        json joutline_info = json::object();
        for (auto it : outline)
        {
            joutline_info["id"] = it.id;
            joutline_info["scene_id"] = it.sceneId;
            joutline_info["map_id"] = it.mapId;
            joutline_info["type"] = it.outlineType;

            json jareas = json::array();
            json jarea = json::array();
            json jareapt = json::object();
            for (auto area : it.region)
            {
                for (auto pt : area)
                {
                    jareapt["x"] = pt.x;
                    jareapt["y"] = pt.y;
                    jarea.push_back(jareapt);
                }
                jareas.push_back(jarea);
            }
            joutline_info["areas"] = jareas;
            joutline_info["alias"] = it.alias;
            joutline_info["object_id"] = it.objectId;
            joutline_info["class_id"] = it.classId;
            joutline_info["stype"] = 1; //此处是经过过滤 类型为1的数据
            joutline_info["semantic_id"] = it.semanticId;

            joutlines.push_back(joutline_info);
        }
        
        msg["code"] = this->code;
        msg["info"] = joutlines;

        return msg.dump();
    }
};


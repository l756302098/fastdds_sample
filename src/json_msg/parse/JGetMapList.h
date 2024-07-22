#pragma once
#include "../../json.hpp"
//#include "msgs/srv/map/OutlineSrv.h"
#include "../../base64.hpp"

using json = nlohmann::json;

struct PointCloud
{
    std::uint64_t   id;
    std::uint64_t   sceneId;
    std::string     sceneName;
    std::uint32_t   useCount;
    std::string     image;
    std::string     thumbnail;
    std::string     path;
    std::uint64_t   date;
    std::uint64_t   lastDate;
    bool valid;
};

class JGetMapListRequest
{
private:
    bool parsed = true;

public:
    std::int64_t time;

    JGetMapListRequest() = delete;
    JGetMapListRequest(const std::string& data)
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

class JGetMapListResponse
{
public:
    int code = 0;
    uint64_t defaultSceneId = 0;
    std::vector<PointCloud> map;

    JGetMapListResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        json jmap = json::object();
        json jmaps = json::array();
        for (auto it : map)
        {
            jmap["scene_id"] = it.sceneId;
            jmap["scene_name"] = it.sceneName;
            jmap["map_id"] = it.id;
            jmap["use_count"] = it.useCount;
            jmap["image"] = it.image;
            jmap["thumbnail"] = it.thumbnail;
            jmap["date"] = it.date;
            jmap["last_date"] = it.lastDate;
            jmap["path"] = it.path;
            if (this->defaultSceneId == it.sceneId)
            {
                jmap["default"] = true;
            }
            else
            {
                jmap["default"] = false;
            }
            jmaps.push_back(jmap);
        }
        msg["code"] = this->code;
        msg["map_list"] = jmaps;

        return msg.dump();
    }
};


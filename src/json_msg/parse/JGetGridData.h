#pragma once
#include "../../json.hpp"
#include "../../base64.hpp"
#include "CommonMsg.h"

using json = nlohmann::json;

class JGetGridDataRequest
{
private:
    bool parsed = true;

public:
    std::string url;

    JGetGridDataRequest() = delete;
    JGetGridDataRequest(const std::string& data)
    {
        nlohmann::json msg = nlohmann::json::parse(data);
        if (msg.contains("url") && msg["url"].is_string())
        {
            url = msg["url"].get<std::string>();
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

class JGetGridDataResponse
{
public:
    int code = 0;
    OccupancyGrid grid;

    JGetGridDataResponse() = default;
    
    std::string toString()
    {
        json msg = json::object();
        msg["width"] = grid.width;
        msg["height"] = grid.height;
        msg["origin_x"] = -30;
        msg["origin_y"] = -30;
        msg["resolution"] = grid.resolution;
        json jdata = json::array();
        json jpt = json::object();
        for (const auto pt : grid.grid_data)
        {
            jpt["x"] = pt.x;
            jpt["y"] = pt.y;
            jpt["type"] = pt.value;
            jdata.push_back(jpt);
        }
        msg["map_info"] = jdata;
        msg["code"] = this->code;

        return msg.dump();
    }
};


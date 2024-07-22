#pragma once
#include "../../json.hpp"
#include "../../base64.hpp"
#include "JGetGridData.h"


class JReportMapIncrement
{
public:
    std::int64_t time = 0;
    OccupancyGrid grid;
    bool parsed;

    JReportMapIncrement() = delete;

    JReportMapIncrement(const std::string& data)
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

        if (msg.contains("width") && msg["width"].is_number())
        {
            grid.width = msg["width"].get<int>();
        }
        else
        {
            this->parsed = false;
        } 

        if (msg.contains("height") && msg["height"].is_number())
        {
            grid.height = msg["height"].get<int>();
        }
        else
        {
            this->parsed = false;
        } 

        if (msg.contains("resolution") && msg["resolution"].is_number())
        {
            grid.resolution = msg["resolution"].get<float>();
        }
        else
        {
            this->parsed = false;
        } 

        if (msg.contains("map_info") && msg["map_info"].is_array())
        {
            for (const auto& item : msg["map_info"])
            {
                int x = item["x"].get<int>();
                int y = item["y"].get<int>();
                int8_t type = item["type"].get<int8_t>();
                grid.grid_data.push_back({x,y,type});
            }
        }
        else
        {
            this->parsed = false;
        }
    }
    
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
            if (pt.value == -1)
            {
                jpt["type"] = 0;
            }
            else
            {
                jpt["type"] = pt.value;
            }
            jdata.push_back(jpt);
        }
        msg["map_info"] = jdata;
        
        return msg.dump();
    }
};
#pragma once

#include <cstdint>
#include <vector>
#include <string>


struct grid
{
    int x;
    int y;
    int8_t value;
    grid(int x_,int y_,int8_t value_)
    {
        x = x_;
        y = y_;
        value = value_;
    }
};

struct OccupancyGrid
{
    std::uint64_t time;
    int width;
    int height;
    float resolution;
    std::vector<grid> grid_data;
};

// 轮廓点集信息类型
enum OutlineType{
    WholeRegion = 0,                        //全区
    Partition = 1,                          //分区
    Region = 2,          				    //划区
	Semantics = 3,               		    //语义
    ForbiddenZone = 4,                      //禁区
    VirtualWall = 5,                        //虚拟墙
    ChargingPile = 6,                       //充电桩
    PartitionBackup = 7,                    //分区备份
    All          = 100,                     //上述所有
};

// struct SemanticObject {
//     semantic_map_msgs::OccupancyMapMsg::ObjectData semanticData;
//     cv::Rect        semanticRect;
//     cv::Mat         semanticImage;
// };

struct Point2f
{
    float x;
    float y;
    Point2f(float x_,float y_)
    {
        x = x_;
        y = y_;
    }
};


struct Outline
{
    std::uint64_t   id;
    std::uint64_t   sceneId;
    std::uint64_t   mapId;
    std::uint16_t   outlineType;
    std::uint16_t   objectId;
    std::uint16_t   classId;
    std::vector<std::vector<Point2f>> region;
    std::string     alias;
    std::uint64_t   date;
    std::uint64_t   lastDate;
    int             semanticId;
    //SemanticObject  semanticObject;

};
#include <iostream>
#include <memory>
#include "wrapper/ServiceWrapper.h"
#include "wrapper/ClientWrapper.h"
#include "report/ReportPublisher.h"
#include "report/ReportSubscriber.h"

#include "json_msg/msgHead.h"

using namespace wk;

class logic
{
private:
    bool init;
    ReportSubscriber hbSub,ipSub,infoSub,stateSub,taskStateSub;
    ReportSubscriber mapSub,poseSub;
    ClientWrapper client;
public:
    logic(/* args */){}
    ~logic(){}
    void init_dds()
    {   
        //topic
        hbSub.init("/indemind/heartbeat",
            std::bind(&logic::OnHeartbeat,this,std::placeholders::_1));
        ipSub.init("/network/ip",
            std::bind(&logic::OnIp,this,std::placeholders::_1));
        infoSub.init("/base/info",
            std::bind(&logic::OnBaseInfo,this,std::placeholders::_1));
        stateSub.init("/robotic/state",
            std::bind(&logic::OnRobotState,this,std::placeholders::_1));
        taskStateSub.init("/task/state",
            std::bind(&logic::OnTaskState,this,std::placeholders::_1));
        //map
        mapSub.init("/map/increment",
            std::bind(&logic::OnMap,this,std::placeholders::_1));
        //pose
        poseSub.init("/map/pose",
            std::bind(&logic::OnPose,this,std::placeholders::_1));
        //service
        client.init("/task/create_map");
    }

    bool start()
    {

        return init;
    }

    void call()
    {
        std::string respStr{};
        JCreateMapRequest createMapReq;
        createMapReq.time = 0;
        if(client.request(createMapReq.toString(),respStr))
        {
            JCreateMapResponse response(respStr);
            std::cout << "response code:" << response.code << " uuid:" << response.uuid << std::endl;
        }
        else
        {
            std::cout << "request failed." << std::endl;
        }
    }

    void OnHeartbeat(const std::string& data)
    {
        std::cout << "data:" << data << std::endl;
        init = true;
    }

    void OnIp(const std::string& data)
    {
        std::cout << "data:" << data << std::endl;
    }

    void OnBaseInfo(const std::string& data)
    {
        std::cout << "data:" << data << std::endl;
    }

    void OnRobotState(const std::string& data)
    {
        std::cout << "data:" << data << std::endl;
    }

    void OnTaskState(const std::string& data)
    {
        std::cout << "data:" << data << std::endl;
    }

    void OnMap(const std::string& data)
    {
        std::cout << "data:" << data << std::endl;
        JReportMapIncrement map(data);
        std::cout << "map width:" << map.grid.width << " height:" << map.grid.height 
            << " angle:"  << map.grid.resolution << std::endl;
        for (const auto& item:map.grid.grid_data)
        {
           std::cout << "map x:" << item.x << " y:" << item.y << " value:"  << item.value << std::endl;
        }
    }

    void OnPose(const std::string& data)
    {
        std::cout << "data:" << data << std::endl;
        JReportPose pose(data);
        std::cout << "pose x:" << pose.x << " y:" << pose.y << " angle:" << pose.angle << std::endl;
    }

};
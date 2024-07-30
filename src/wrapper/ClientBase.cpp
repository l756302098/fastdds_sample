#include "ClientBase.h"

namespace wk {
    std::int64_t ClientBase::index = 0;
    bool ClientBase::init(std::string name)
    {
        if(publisher_.init(name))
        {
            return subscription_.init(name,
                std::bind(&ClientBase::on_response,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
        }
        return false;
    }

    bool ClientBase::request(const std::string& topic,const std::string& req,std::string& resp)
    {
        ++ClientBase::index;
        if(!publisher_.publish(ClientBase::index,topic,req))
        {
            SLOG(INFO) << "request publish failed.";
            return false;
        }
        //wait for response
        std::unique_lock lk(mtx);
        if(cv.wait_for(lk,std::chrono::seconds(60))==std::cv_status::timeout)
        {
            SLOG(INFO) << "request timeout." << std::endl;
            return false;
        }
        resp = respData;
        return true;
    }

    void ClientBase::on_response(const int64_t index,const std::string& topic,const std::string& data)
    {
        std::cout << __func__ << index << " data:" << data << std::endl;
        //notify one
        {
            std::lock_guard<std::mutex> guard(mtx);
            respData = data;
        }
        cv.notify_one();
    }

}
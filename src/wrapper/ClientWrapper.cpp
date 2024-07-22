#include "ClientWrapper.h"

namespace wk {
    std::int64_t ClientWrapper::index = 0;
    bool ClientWrapper::init(std::string name)
    {
        if(publisher_.init(name))
        {
            return subscription_.init(name,
                std::bind(&ClientWrapper::on_response,this,std::placeholders::_1,std::placeholders::_2));
        }
        return false;
    }

    bool ClientWrapper::request(const std::string& data,std::string& resp)
    {
        ++ClientWrapper::index;
        if(!publisher_.publish(ClientWrapper::index,data))
        {
            std::cout << "request publish failed." << std::endl;
            return false;
        }
        //wait for response
        std::unique_lock lk(mtx);
        if(cv.wait_for(lk,std::chrono::seconds(60))==std::cv_status::timeout)
        {
            std::cout << "request timeout." << std::endl;
            return false;
        }
        resp = respData;
        return true;
    }

    void ClientWrapper::on_response(const int64_t index,const std::string& data)
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
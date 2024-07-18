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

    bool ClientWrapper::request(const std::string& data)
    {
        ++ClientWrapper::index;
        if(!publisher_.publish(ClientWrapper::index,data))
        {
            std::cout << "request publish failed." << std::endl;
            return false;
        }
        //wait for response
        
        return true;
    }

    void ClientWrapper::on_response(const int64_t index,const std::string& data)
    {
        std::cout << __func__ << index << " data:" << data << std::endl;
        //notify one
        
    }

}
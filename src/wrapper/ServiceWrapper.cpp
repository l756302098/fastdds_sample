#include "ServiceWrapper.h"

namespace wk {

    bool ServiceWrapper::init(std::string name,std::function<void(const int64_t,const std::string&)> cb)
    {
        if(publisher_.init(name))
        {
            return subscription_.init(name,cb);
        }
        return false;
    }

    bool ServiceWrapper::reply(const int64_t index,const std::string& data)
    {
        return publisher_.publish(index,data);
    }
}
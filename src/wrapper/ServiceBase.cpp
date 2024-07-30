#include "ServiceBase.h"

namespace wk {

    bool ServiceBase::init(std::string name,std::function<void(const int64_t,const std::string&,const std::string&)> cb)
    {
        if(publisher_.init(name))
        {
            return subscription_.init(name,cb);
        }
        return false;
    }

    bool ServiceBase::reply(const int64_t index,const std::string& topic,const std::string& data)
    {
        return publisher_.publish(index,topic,data);
    }
}
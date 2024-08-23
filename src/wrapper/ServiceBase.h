#pragma once
#include "../request/RequestSubscriber.h"
#include "../response/ResponsePublisher.h"
#include "../log_define.h"

namespace wk {
    class ServiceBase
    {
    private:
        ResponsePublisher publisher_;
        RequestSubscriber subscription_;
    public:
        ServiceBase();
        ~ServiceBase();
        bool init(std::string name,std::function<void(const int64_t,const std::string&,const std::string&)> cb);
        bool reply(const int64_t index,const std::string& topic,const std::string& data);
    };
}
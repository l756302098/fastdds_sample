#include "ServiceWrapper.h"

namespace wk {

    std::atomic_bool ServiceWrapper::is_init_ = false;
    ServiceBase *ServiceWrapper::service_ = nullptr;
    ServiceWrapper::OpSMap ServiceWrapper::del_map_ = {};
    std::mutex ServiceWrapper::mtx = {};

    ServiceWrapper::ServiceWrapper(/* args */){}

    ServiceWrapper::~ServiceWrapper()
    {
        auto it = ServiceWrapper::del_map_.find(topic_);
        if(it!=ServiceWrapper::del_map_.end())
        {
            ServiceWrapper::del_map_.erase(it);
        }
        cleanup();
    }

    bool ServiceWrapper::init(std::string name,std::function<void(const int64_t,const std::string&)> cb)
    {
        if(!ServiceWrapper::is_init_)
        {
            SLOG(INFO) << __func__ << " init.";
            std::lock_guard<std::mutex> guard(mtx);
            ServiceWrapper::service_ = new ServiceBase();
            ServiceWrapper::service_->init(service_name_,
                std::bind(&ServiceWrapper::OnCB, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            ServiceWrapper::is_init_ = true;
        }
        ServiceWrapper::del_map_.emplace(std::make_pair(name,cb));
        topic_ = name;
        return true;
    }

    bool ServiceWrapper::reply(const int64_t index,const std::string& data)
    {
        std::lock_guard<std::mutex> guard(mtx);
        return ServiceWrapper::service_->reply(index,topic_,data);
    }

    void ServiceWrapper::OnCB(const int64_t index,const std::string& topic,const std::string& data)
    {
        auto it = ServiceWrapper::del_map_.find(topic);
        if(it!=ServiceWrapper::del_map_.end())
        {
            it->second(index,data);
        }
    }

    void ServiceWrapper::cleanup()
    {
        std::lock_guard<std::mutex> guard(mtx);
        if(ServiceWrapper::is_init_ && ServiceWrapper::service_!=nullptr)
        {
            delete ServiceWrapper::service_;
            ServiceWrapper::service_ = nullptr;
        }
        ServiceWrapper::is_init_ = false;
    }
}
#include "SubscriberWrapper.h"

namespace wk {
std::atomic_bool SubscriberWrapper::is_init_ = false;
ReportSubscriber *SubscriberWrapper::sub_ = {};
SubscriberWrapper::OpMap SubscriberWrapper::del_map_ = {};
std::shared_mutex SubscriberWrapper::mtx = {};
std::mutex SubscriberWrapper::sub_mtx = {};
std::int64_t SubscriberWrapper::index = 0;

SubscriberWrapper::SubscriberWrapper(/* args */){}

SubscriberWrapper::~SubscriberWrapper()
{
    //remove
    {
        std::lock_guard<std::shared_mutex> guard(mtx);
        auto it = SubscriberWrapper::del_map_.find(topic_);
        if(it!=SubscriberWrapper::del_map_.end())
        {
            std::vector<SubscriberOp> &sos = it->second;
            for (std::vector<SubscriberOp>::iterator its = sos.begin(); its != sos.end();)
            {
                if(its->id == id_)
                {
                    sos.erase(its);
                    break;
                }
                else
                {
                    ++its;
                }
            }
        }
    }
    cleanup();
}

bool SubscriberWrapper::init(const std::string& topic,std::function<void(const std::string&)> cb)
{
    if(!SubscriberWrapper::is_init_)
    {
        std::cout << __func__ << " init" << std::endl;
        std::lock_guard<std::mutex> guard(sub_mtx);
        SubscriberWrapper::sub_ = new ReportSubscriber();
        SubscriberWrapper::sub_->init(report_topic_,
            std::bind(&SubscriberWrapper::on_cb, this, std::placeholders::_1, std::placeholders::_2));
        SubscriberWrapper::is_init_ = true;
    }
    {
        std::lock_guard<std::shared_mutex> guard(mtx);
        id_ = ++SubscriberWrapper::index;
        SubscriberOp so;
        so.id = id_;
        so.cb = cb;
        auto it = SubscriberWrapper::del_map_.find(topic);
        if(it!=SubscriberWrapper::del_map_.end())
        {
            it->second.push_back(so);
        }
        else
        {
            std::vector<SubscriberOp> ops;
            ops.push_back(so);
            SubscriberWrapper::del_map_.emplace(std::make_pair(topic,ops));
        }
    }
    topic_ = topic;
    return true;
}

void SubscriberWrapper::remove_cb()
{
    std::lock_guard<std::shared_mutex> guard(mtx);
    auto it = SubscriberWrapper::del_map_.find(topic_);
    if(it!= SubscriberWrapper::del_map_.end())
    {
        std::vector<SubscriberOp> &sos = it->second;
        for (std::vector<SubscriberOp>::iterator its = sos.begin(); its != sos.end();)
        {
            if(its->id == id_)
            {
                sos.erase(its);
                break;
            }
            else
            {
                ++its;
            }
        }
    }
}

void SubscriberWrapper::on_cb(const std::string& topic,const std::string& data)
{
    std::lock_guard<std::shared_mutex> guard(mtx);
    auto it = SubscriberWrapper::del_map_.find(topic);
    if(it!=SubscriberWrapper::del_map_.end())
    {
        for (const auto& op:it->second)
        {
            op.cb(data);
        } 
    }
}

void SubscriberWrapper::cleanup()
{
    std::lock_guard<std::mutex> guard(sub_mtx);
    if(SubscriberWrapper::is_init_ && SubscriberWrapper::sub_!=nullptr)
    {
        delete SubscriberWrapper::sub_;
        SubscriberWrapper::sub_ = nullptr;
    }
    SubscriberWrapper::is_init_ = false;
}

}
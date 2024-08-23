#include "PublisherWrapper.h"

namespace wk {

std::atomic_bool PublisherWrapper::is_init_ = false;
ReportPublisher *PublisherWrapper::pub_ = nullptr;
std::mutex PublisherWrapper::mtx = {};

PublisherWrapper::PublisherWrapper(/* args */)
{
    
}

PublisherWrapper::~PublisherWrapper()
{
    cleanup();
}

bool PublisherWrapper::init(const std::string& topic)
{
    if(!PublisherWrapper::is_init_)
    {
        std::cout << __func__ << " init" << std::endl;
        PublisherWrapper::pub_ = new ReportPublisher();
        PublisherWrapper::pub_->init(report_topic_);
        PublisherWrapper::is_init_ = true;
    }
    topic_ = topic;
    return true;
}

bool PublisherWrapper::publish(const std::string& data)
{
    if(PublisherWrapper::is_init_)
    {
        std::lock_guard<std::mutex> guard(mtx);
        long size = sizeof(data);
        if(size > 512 * 1024)
        {
            SLOG(INFO) << "send size:" << size << " data:"<< data;
        }
        if(!PublisherWrapper::pub_->publish(topic_,data))
        {
            SLOG(INFO) << "send size:" << size << " failed.";
            return false;
        }
        return true;
    }
    return false;
}

void PublisherWrapper::cleanup()
{
    std::lock_guard<std::mutex> guard(mtx);
    if(PublisherWrapper::is_init_ && PublisherWrapper::pub_!=nullptr)
    {
        delete PublisherWrapper::pub_;
        PublisherWrapper::pub_ = nullptr;
    }
    PublisherWrapper::is_init_ = false;
}

}
#include "PublisherWrapper.h"

namespace wk {

std::atomic_bool PublisherWrapper::is_init_ = false;
ReportPublisher PublisherWrapper::pub_ = {};

PublisherWrapper::PublisherWrapper(/* args */)
{
}

PublisherWrapper::~PublisherWrapper()
{
}

bool PublisherWrapper::init(const std::string& topic)
{
    if(!PublisherWrapper::is_init_)
    {
        std::cout << __func__ << " init" << std::endl;
        pub_.init(report_topic_);
        PublisherWrapper::is_init_ = true;
    }
    topic_ = topic;
    return true;
}

bool PublisherWrapper::publish(const std::string& data)
{
    if(PublisherWrapper::is_init_)
    {
        PublisherWrapper::pub_.publish(topic_,data);
        return true;
    }
    return false;
}
}
#pragma once

#include "../report/ReportPublisher.h"
namespace wk {
class PublisherWrapper
{
private:
    const std::string report_topic_ = "/indemind/topic";
    static std::atomic_bool is_init_;
    static ReportPublisher pub_;
    std::string topic_;
public:
    PublisherWrapper(/* args */);
    ~PublisherWrapper();
    bool init(const std::string& topic);
    bool publish(const std::string& data);
};
}
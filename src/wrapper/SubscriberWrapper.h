#pragma once

#include "../report/ReportSubscriber.h"
#include <unordered_map>
#include <string>
#include <shared_mutex>
#include <mutex>
namespace wk {

struct SubscriberOp
{
    std::int64_t id;
    std::function<void(const std::string&)> cb;
};


class SubscriberWrapper
{
private:
    const std::string report_topic_ = "/tcl/topic";
    static std::atomic_bool is_init_;
    static ReportSubscriber *sub_;
    typedef std::unordered_map<std::string,std::vector<SubscriberOp>> OpMap;
    static OpMap del_map_;
    static std::shared_mutex mtx;
    static std::mutex sub_mtx;
    static std::int64_t index;
    std::int64_t id_;
    std::string topic_;
    void on_cb(const std::string& topic,const std::string& data);
public:
    SubscriberWrapper(/* args */);
    ~SubscriberWrapper();
    bool init(const std::string& topic,std::function<void(const std::string&)> cb = nullptr);
    void remove_cb();
    static void cleanup();
};
}
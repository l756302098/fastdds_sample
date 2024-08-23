#pragma once

#include "ServiceBase.h"
#include <unordered_map>
#include <mutex>
namespace wk {
class ServiceWrapper
{
private:
    const std::string service_name_ = "/tcl2indemind";
    static std::atomic_bool is_init_;
    static ServiceBase *service_;
    static std::mutex mtx;
    std::string topic_;
    typedef std::unordered_map<std::string,std::function<void(const int64_t&,const std::string&)>> OpSMap;
    static OpSMap del_map_;
    void OnCB(const int64_t index,const std::string& topic,const std::string& data);
public:
    ServiceWrapper(/* args */);
    ~ServiceWrapper();
    bool init(std::string name,std::function<void(const int64_t,const std::string&)> cb);
    bool reply(const int64_t index,const std::string& data);
    static void cleanup();
};
}
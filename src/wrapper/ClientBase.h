#pragma once
#include "../request/RequestPublisher.h"
#include "../response/ResponseSubscriber.h"
#include "../log_define.h"
#include <mutex>
#include <condition_variable>

namespace wk {
    class ClientBase
    {
    private:
        RequestPublisher publisher_;
        ResponseSubscriber subscription_;
        std::mutex mtx;
        std::condition_variable cv;
        std::string respData;
    public:
        static std::int64_t index;
    public:
        ClientBase() = default;
        ~ClientBase() = default;
        bool init(std::string name);
        bool request(const std::string& topic,const std::string& req,std::string& resp);
        void on_response(const int64_t index,const std::string& topic,const std::string& data);
    };
}
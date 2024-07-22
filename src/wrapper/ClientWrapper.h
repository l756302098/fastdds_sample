#pragma once
#include "../request/RequestPublisher.h"
#include "../response/ResponseSubscriber.h"
#include <mutex>
#include <condition_variable>


namespace wk {
    class ClientWrapper
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
        ClientWrapper() = default;
        ~ClientWrapper() = default;
        bool init(std::string name);
        bool request(const std::string& data,std::string& resp);
        void on_response(const int64_t index,const std::string& data);
    };
}
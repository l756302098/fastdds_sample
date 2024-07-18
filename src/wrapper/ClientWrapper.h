#pragma once
#include "request/RequestPublisher.h"
#include "response/ResponseSubscriber.h"
#include "../log_define.h"

namespace wk {
    class ClientWrapper
    {
    private:
        RequestPublisher publisher_;
        ResponseSubscriber subscription_;
    public:
        static std::int64_t index;
    public:
        ClientWrapper() = default;
        ~ClientWrapper() = default;
        bool init(std::string name);
        bool request(const std::string& data);
        void on_response(const int64_t index,const std::string& data);
    };
}
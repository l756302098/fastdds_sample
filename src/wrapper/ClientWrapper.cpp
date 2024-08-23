#include "ClientWrapper.h"

namespace wk {
    std::atomic_bool ClientWrapper::is_init_ = false;
    ClientBase *ClientWrapper::client_ = {};
    std::mutex ClientWrapper::mtx = {};
    ClientWrapper::~ClientWrapper()
    {
        cleanup();
    }

    bool ClientWrapper::init(std::string name)
    {
        if(!is_init_)
        {
            client_ = new ClientBase();
            client_->init(client_name_);
            is_init_ = true;
        }
        topic_ = name;
        return true;
    }

    bool ClientWrapper::request(const std::string& req,std::string& resp)
    {
        std::lock_guard<std::mutex> guard(mtx);
        if(!is_init_)
        {
            SLOG(INFO) << __func__ << " not init.";
            return false;
        }
        return client_->request(topic_,req,resp);
    }

    void ClientWrapper::cleanup()
    {
        std::lock_guard<std::mutex> guard(mtx);
        if(ClientWrapper::is_init_ && ClientWrapper::client_!=nullptr)
        {
            delete ClientWrapper::client_;
            ClientWrapper::client_ = nullptr;
        }
        ClientWrapper::is_init_ = false;
    }

}
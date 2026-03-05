#ifndef EVENT_HPP
#define EVENT_HPP

#include "Client.hpp"
#include "ListeningSocket.hpp"
#include "EpollManager.hpp"
#include "HttpReq.hpp"
#include "ManageServers.hpp"
#include <map>
#include <vector>

class Event{
    private:
        int _clientFd;
        std::map<int, HttpRequest> requests;
        
    public:
        Event();
        ~Event();
        void run(SocketManager& manager, EpollManager& epollManager);
};



#endif
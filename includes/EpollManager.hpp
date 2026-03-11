#ifndef EPOLLMANAGER_HPP
#define EPOLLMANAGER_HPP

#include "ManageServers.hpp"
#include <sys/epoll.h>

class EpollManager {
    private:
        int _epollFd;
    public:
        EpollManager();
        ~EpollManager();
        void ctrl(int fd, uint32_t events, int operation);
        std::vector<struct epoll_event> wait(int timeout);
};
#endif
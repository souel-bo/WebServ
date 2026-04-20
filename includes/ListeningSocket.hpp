#ifndef LISTENINGSOCKET_HPP
#define LISTENINGSOCKET_HPP

#include "Config.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdexcept>
#include <arpa/inet.h>
#include <fcntl.h>

class ListeningSocket {
private:
    int _fd;
    ServerConfig* _server;
    std::string error;

public:
    ListeningSocket();
    ListeningSocket(ServerConfig* server);
    ~ListeningSocket();
    void createSocket();
    void setReuseAddr();
    void bindSocket();
    void startListening(int backlog);
    void setNonBlocking();
    int getFd() const;
    int getPort() const ;
    ServerConfig* getServer() const;
    std::string get_error();
};


#endif
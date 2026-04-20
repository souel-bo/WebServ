#include "ListeningSocket.hpp"

ListeningSocket::ListeningSocket(): _fd(-1), _server(0){}

ListeningSocket::ListeningSocket(ServerConfig* server) : _fd(-1), _server(server) {}

ListeningSocket::~ListeningSocket() {
    if (_fd != -1) {
        close(_fd);
    }
}

void ListeningSocket::createSocket() {
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_fd == -1) {
        ListeningSocket  temp;
        temp.error = "Failed to create socket";
        throw temp;
    }
}

void ListeningSocket::setReuseAddr() {
    int opt = 1;
    if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        ListeningSocket  temp;
        temp.error = "Failed To Reuse_addr";
        throw temp;
    }
}

void ListeningSocket::bindSocket() {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_server->port);
    addr.sin_addr.s_addr = inet_addr(_server->host.c_str());

    if (bind(_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        ListeningSocket  temp;
        temp.error = "Failed to bind socket";
        throw temp;
    }
}

void ListeningSocket::startListening(int backlog) {
    if (listen(_fd, backlog) == -1) {
        ListeningSocket  temp;
        temp.error = "Failed to listen to socket";
        throw temp;
    }
}

void ListeningSocket::setNonBlocking() {
    int flags = fcntl(_fd, F_GETFL, 0);
    if (flags == -1) {
        ListeningSocket  temp;
        temp.error = "Failed to get socket flag";
        throw temp;
    }
    if (fcntl(_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        ListeningSocket  temp;
        temp.error = "Failed to set socket non blocking";
        throw temp;
    }
}

int ListeningSocket::getFd() const {
    return _fd;
}

int ListeningSocket::getPort() const {
    return _server->port;
}

ServerConfig* ListeningSocket::getServer() const {
    return _server;
}
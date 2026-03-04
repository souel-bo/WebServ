#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "Config.hpp"
#include "HttpReq.hpp"
#include <string>

struct RouteResult
{
    bool        isAllowed;
    Location    location;
    std::string finalPath;
};

class Router
{
    private:
        static std::string joinPaths(const std::string& path1, const std::string& path2);
    public:
        Router();
        ~Router();
        static RouteResult resolve(const HttpRequest& req, const ServerConfig& config);
};

#endif
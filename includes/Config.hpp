#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include <map>

class Location {
    public:
        std::string                 path;
        std::string                 root;
        bool                        autoindex;
        std::string                 index;
        std::vector<std::string>    methods;
        std::string                 returnPath;
        int                         returnCode;
        std::string                 alias;
        unsigned long               maxBodySize;
        bool                       is_Redirect;
        Location() : path(""), root(""), autoindex(false), index(""), returnPath(""), returnCode(0), alias(""), maxBodySize(0), is_Redirect(false) {}
};

class ServerConfig {
    public:
        int                         port;
        std::string                 host;
        std::vector<std::string>    serverNames;
        std::string                 root;
        std::map<int, std::string>  errorPages;
        unsigned long               maxBodySize;
        std::vector<Location>       locations;

        ServerConfig() : port(80), host("127.0.0.1"), root(""), maxBodySize(1000000) {}
};

#endif
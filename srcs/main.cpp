#include "../includes/ConfigParser.hpp"
#include <iostream>
#include "ManageServers.hpp"
#include "ListeningSocket.hpp"
#include "EpollManager.hpp"
#include "Event.hpp"


bool hasConfExtension(const std::string& filepath) 
{
    size_t slashPos = filepath.find_last_of('/');
    std::string filename = (slashPos == std::string::npos) ? filepath : filepath.substr(slashPos + 1);
    if (filename.length() < 6) 
        return false;
    if (filename.substr(filename.length() - 5) != ".conf")
        return false;
    int dotCount = 0;
    for (size_t i = 0; i < filename.length(); i++) 
    {
        if (filename[i] == '.') 
            dotCount++;
    }
    if (dotCount > 1) 
        return false;

    return true;
}

int main(int argc, char **argv)
{
    std::string configFile;
    if (argc == 1) 
    {
        std::cout << "No config file provided. Defaulting to 'webserv.conf'..." << std::endl;
        configFile = "webserv.conf"; 
    } 
    else if (argc == 2) 
    {
        configFile = argv[1];
    } 
    else 
    {
        std::cerr << "Usage: ./webserv [config_file.conf]" << std::endl;
        return 1;
    }
    if (!hasConfExtension(configFile)) 
    {
        std::cerr << "Error: Configuration file MUST end with '.conf' (e.g., webserv.conf)" << std::endl;
        return 1;
    }
    try
    {
        ConfigParser parser;
        parser.parse(configFile);
        
        std::vector<ServerConfig> servers = parser.getServers();
        std::cout << "Successfully parsed config file!" << std::endl;
        std::cout << "Found " << servers.size() << " servers." << std::endl;
        
        if (!servers.empty())
        {
            SocketManager manager;
            manager.generateListeningSockets(servers);
            std::vector<int> fds = manager.getFds();
            EpollManager epollManager;
            for (size_t i = 0; i < fds.size(); ++i)
                epollManager.ctrl(fds[i], EPOLLIN, EPOLL_CTL_ADD);
                
            Event event;
            event.run(manager, epollManager);
        }
    } 
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
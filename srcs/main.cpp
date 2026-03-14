#include "../includes/ConfigParser.hpp"
#include <iostream>
#include "ManageServers.hpp"
#include "ListeningSocket.hpp"
#include "EpollManager.hpp"
#include "Event.hpp"


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./webserv [config_file]" << std::endl;
        return 1;
    }
    try
    {
        ConfigParser parser;
        parser.parse(argv[1]);
        std::vector<ServerConfig> servers = parser.getServers();
        std::cout << "Successfully parsed config file!" << std::endl;
        for (size_t i = 0; i < servers.size(); ++i)
        {
            for (size_t j = 0; j < servers[i].locations.size(); ++j)
            {
                if (!servers[i].locations[j].returnPath.empty())
                    std::cout << "Server " << servers[i].port
                              << " | location " << servers[i].locations[j].path
                              << " -> " << servers[i].locations[j].returnCode
                              << " " << servers[i].locations[j].returnPath << std::endl;
            }
        }
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
            // manager.cleanup();
        }
    } catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
// =======
//     try
//     {
//         ConfigParser parser;
//         parser.parse(argv[1]);
//         std::vector<ServerConfig> servers = parser.getServers();
//         std::cout << "Successfully parsed config file!" << std::endl;
//         std::cout << "Found " << servers.size() << " servers." << std::endl;
//         if (!servers.empty())
//         {
            
//             std::cout << "Server 1 listening on port: " << servers[0].port << std::endl;
//             std::cout << "Server 1 root: " << servers[0].locations[0].root << std::endl;
//         }
//     } catch (const std::exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//     }

//     return 0;
// }
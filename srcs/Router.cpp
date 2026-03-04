#include "../includes/Router.hpp"
#include <iostream>

Router::Router() {}
Router::~Router() {}

std::string Router::joinPaths(const std::string& path1, const std::string& path2)
{
    if (path1.empty())
        return path2;
    if (path2.empty())
        return path1;
    bool path1HasSlash = (path1[path1.length() - 1] == '/');
    bool path2HasSlash = (path2[0] == '/');
    if (path1HasSlash && path2HasSlash)
        return path1 + path2.substr(1);
    if (!path1HasSlash && !path2HasSlash)
        return path1 + "/" + path2;
    return path1 + path2;
}

RouteResult Router::resolve(const HttpRequest& req, const ServerConfig& config)
{
    RouteResult result;
    result.isAllowed = true;
    std::string uri = req.getPath();
    const Location* bestMatch = NULL;
    size_t longestMatchLength = 0;
    for (size_t i = 0; i < config.locations.size(); ++i)
    {
        const std::string& locPath = config.locations[i].path;
        if (uri.find(locPath) == 0)
        {
            if (locPath.length() > longestMatchLength)
            {
                longestMatchLength = locPath.length();
                bestMatch = &config.locations[i];
            }
        }
    }
    if (bestMatch != NULL)
    {
        result.location = *bestMatch;
        bool methodFound = false;
        if (bestMatch->methods.empty())
        {
            methodFound = true;
        } else
        {
            for (size_t i = 0; i < bestMatch->methods.size(); ++i)
            {
                if (bestMatch->methods[i] == req.getMethod())
                {
                    methodFound = true;
                    break;
                }
            }
        }
        if (!methodFound)
        {
            result.isAllowed = false;
        }
        if (!bestMatch->alias.empty())
        {
            std::string remainingUri = uri.substr(longestMatchLength);
            result.finalPath = joinPaths(bestMatch->alias, remainingUri);
        } else if (!bestMatch->root.empty())
        {
            result.finalPath = joinPaths(bestMatch->root, uri);
        } else
        {
            result.finalPath = joinPaths(config.root, uri);
        }
    } 
    else
    {
        result.finalPath = joinPaths(config.root, uri);
    }
    return result;
}
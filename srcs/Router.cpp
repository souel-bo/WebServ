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


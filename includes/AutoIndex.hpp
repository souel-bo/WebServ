#ifndef AUTOINDEX_HPP
#define AUTOINDEX_HPP

#include <string>

class AutoIndex
{
    public:
        static std::string generate(const std::string& physicalPath, const std::string& requestedUri);
};

#endif
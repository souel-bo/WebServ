#include "../includes/AutoIndex.hpp"
#include <dirent.h>
#include <sys/stat.h>
#include <sstream>

std::string AutoIndex::generate(const std::string& physicalPath, const std::string& requestedUri)
{
    DIR* dir = opendir(physicalPath.c_str());
    if (dir == NULL)
        return ""; // 403
    std::string uri = requestedUri;
    if (!uri.empty() && uri[uri.length() - 1] != '/')
        uri += "/";
    std::stringstream html;
    html << "<!DOCTYPE html>\n<html>\n<head><title>Index of " << uri << "</title></head>\n<body>\n";
    html << "<h1>Index of " << uri << "</h1>\n<hr>\n<pre>\n";
    html << "<a href=\"../\">../</a>\n";
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL)
    {
        std::string name = entry->d_name;
        if (name == "." || name == "..")
            continue;
        std::string fullPath = physicalPath;
        if (fullPath[fullPath.length() - 1] != '/')
            fullPath += "/";
        fullPath += name;
        struct stat statbuf;
        if (stat(fullPath.c_str(), &statbuf) == 0)
        {
            if (S_ISDIR(statbuf.st_mode))
            {
                name += "/";
            }
        }
        html << "<a href=\"" << uri << name << "\">" << name << "</a>\n";
    }
    closedir(dir);
    html << "</pre>\n<hr>\n</body>\n</html>\n";
    return html.str();
}
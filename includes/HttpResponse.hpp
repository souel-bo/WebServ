#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "HttpReq.hpp"
#include "Router.hpp"
#include <map>
#include <string>
#include <fcntl.h>
#include <unistd.h>

class HttpResponse : public HttpRequest, public Router {
    private:
        std::string status_line;
        std::map<std::string, std::string> response_headers;
        std::string response_body;
        std::string content_type;
        std::string content_length;
        std::string connection;
        int status_code;
    public :
        void generateResponse(const HttpRequest& req,  RouteResult& routeResult);
        void setStatusLine(std::string &path);
        void setResponseHeaders(const std::map<std::string, std::string>& headers);
        void setResponseBody(const std::string& body);
        const std::string& getStatusLine() const;
        const std::map<std::string, std::string>& getResponseHeaders() const;
        std::string &find_requested_file(std::string& path);
        const std::string& getResponseBody() const;
};

#endif
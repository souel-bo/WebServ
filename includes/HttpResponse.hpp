#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "HttpReq.hpp"
#include "Router.hpp"

class HttpResponse : public HttpRequest, public Router {
    private:
        std::string status_line;
        std::map<std::string, std::string> response_headers;
        std::string response_body;
        int status_code;
    public :
        void generateResponse(const HttpRequest& req, const Router& routeResult);
        void setStatusLine(int code);
        void setResponseHeaders(const std::map<std::string, std::string>& headers);
        void setResponseBody(const std::string& body);
        const std::string& getStatusLine() const;
        const std::map<std::string, std::string>& getResponseHeaders() const;
        const std::string& getResponseBody() const;
};

#endif
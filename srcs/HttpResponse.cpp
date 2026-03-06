#include "HttpResponse.hpp"

void HttpResponse::setStatusLine(std::string &path)
{
    int fd = open(path.c_str(), O_RDONLY);
    if (fd == -1)
    {
        status_line = "HTTP/1.1 404 Not Found\r\n";
        status_code = 404;
    }
    else
    {
        status_line = "HTTP/1.1 200 OK\r\n";
        status_code = 200;
    }
}

const std::string& HttpResponse::getStatusLine() const
{
    return status_line;
}

void HttpResponse::setResponseHeaders(const std::map<std::string, std::string>& headers)
{
    response_headers = headers;
}

void HttpResponse::generateResponse(const HttpRequest& req, RouteResult& routeResult)
{
    // │
    // ├─ 1. Determine if the requested file exists
    // │      └─ Set status code (200, 404, etc.)
    // │
    // ├─ 2. Set the status line
    // │      └─ Example: "HTTP/1.1 200 OK\r\n"
    // │
    // ├─ 3. Decide transfer method
    // │      ├─ Small file → Content-Length
    // │      └─ Large file / streaming → Chunked Transfer-Encoding
    // │
    // ├─ 4. Set headers
    // │      ├─ Content-Type (based on file extension)
    // │      ├─ Content-Length (if small file)
    // │      ├─ Transfer-Encoding: chunked (if streaming)
    // │      ├─ Connection: close
    // │      └─ Server: webserv
    // │
    // ├─ 5. Prepare the body
    // │      ├─ Small file → read all into memory
    // │      └─ Large file → don’t read all at once, prepare for streaming
    // │
    // └─ 6. Response is ready to send
    //        ├─ Small file → send in one go
    //        └─ Large file → send in chunks from file
}
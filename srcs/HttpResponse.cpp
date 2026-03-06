#include "HttpResponse.hpp"

const std::string& HttpResponse::getStatusLine() const
{
    return status_line;
}

void HttpResponse::setResponseHeaders(const std::map<std::string, std::string>& headers)
{
    response_headers = headers;
}

void HttpResponse::setStatusLine(int code)
{
    status_code = code;

    switch (code)
    {
        case 200:
            status_line = "HTTP/1.1 200 OK\r\n";
            break;
        case 301:
            status_line = "HTTP/1.1 301 Moved Permanently\r\n";
            break;
        case 302:
            status_line = "HTTP/1.1 302 Found\r\n";
            break;
        case 400:
            status_line = "HTTP/1.1 400 Bad Request\r\n";
            break;
        case 403:
            status_line = "HTTP/1.1 403 Forbidden\r\n";
            break;
        case 404:
            status_line = "HTTP/1.1 404 Not Found\r\n";
            break;
        case 405:
            status_line = "HTTP/1.1 405 Method Not Allowed\r\n";
            break;
        case 500:
            status_line = "HTTP/1.1 500 Internal Server Error\r\n";
            break;
        case 501:
            status_line = "HTTP/1.1 501 Not Implemented\r\n";
            break;
        case 503:
            status_line = "HTTP/1.1 503 Service Unavailable\r\n";
            break;
        default:
            status_line = "HTTP/1.1 500 Internal Server Error\r\n";
            status_code = 500;
            break;
    }
}

void HttpResponse::decideStatus(const HttpRequest& req, const std::string& path, bool serverError)
{
    int code;
    struct stat fileStat;
    if (req.getMethod() != "GET" && req.getMethod() != "POST" && req.getMethod() != "DELETE")
        code = 405;
    else
    {
        if (stat(path.c_str(), &fileStat) != 0)
            code = 404;
        else if (!S_ISREG(fileStat.st_mode))
            code = 403;
        else
        {
            int fd = open(path.c_str(), O_RDONLY);
            if (fd == -1)
                code = 403;
            else
            {
                if (serverError)
                    code = 500;
                else
                    code = 200;
                close(fd);
            }
        }
    }
    setStatusLine(code);
    fileSize = fileStat.st_size;
}



void HttpResponse::generateResponse(const HttpRequest& req, RouteResult& routeResult)
{
    decideStatus(req, routeResult.finalPath, !routeResult.isAllowed);
    if (fileSize < 1024 *1024)
        setResponseBody(find_requested_file(routeResult.finalPath));
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
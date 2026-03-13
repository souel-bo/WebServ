#include "../includes/SessionManager.hpp"
#include "../includes/HttpResponse.hpp"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

std::map<std::string, Session> sessions;

static std::string trimSpaces(const std::string& value)
{
    if (value.empty())
        return value;
    size_t start = value.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = value.find_last_not_of(" \t\r\n");
    return value.substr(start, end - start + 1);
}

std::string extractSessionId(const HttpRequest& req)
{
    const std::map<std::string, std::string>& headers = req.getHeaders();
    std::map<std::string, std::string>::const_iterator it = headers.find("Cookie");
    if (it == headers.end())
        return "";

    const std::string& cookieHeader = it->second;
    size_t start = 0;

    while (start < cookieHeader.size())
    {
        size_t end = cookieHeader.find(';', start);
        std::string pair = (end == std::string::npos)
            ? cookieHeader.substr(start)
            : cookieHeader.substr(start, end - start);

        size_t eq = pair.find('=');
        if (eq != std::string::npos)
        {
            std::string key = trimSpaces(pair.substr(0, eq));
            std::string value = trimSpaces(pair.substr(eq + 1));
            if (key == "session_id")
                return value;
        }

        if (end == std::string::npos)
            break;
        start = end + 1;
    }

    return "";
}

std::string generateSessionId()
{
    static bool seeded = false;
    static unsigned long counter = 0;

    if (!seeded)
    {
        std::srand(static_cast<unsigned int>(std::time(NULL) ^ getpid()));
        seeded = true;
    }
    std::string id;
    do
    {
        std::ostringstream oss;
        oss << std::hex;
        oss << std::time(NULL);
        oss << std::rand();
        oss << ++counter;
        oss << getpid();
        id = oss.str();
    } while (sessions.find(id) != sessions.end());
    return id;
}

Session& createSession()
{
    Session session;
    session.id = generateSessionId();
    session.logged_in = false;
    sessions[session.id] = session;
    return sessions[session.id];
}

bool isSessionValid(const std::string& sessionId)
{
    if (sessionId.empty())
        return false;
    return sessions.find(sessionId) != sessions.end();
}

void attachSetCookieHeader(HttpResponse& res, const std::string& sessionId)
{
    res.setHeader("Set-Cookie", "session_id=" + sessionId + "; Path=/");
}

std::string extractQueryParam(const std::string& path, const std::string& key)
{
    size_t question = path.find('?');
    if (question == std::string::npos)
        return "";

    std::string query = path.substr(question + 1);
    size_t start = 0;
    while (start < query.size())
    {
        size_t amp = query.find('&', start);
        std::string token = (amp == std::string::npos)
            ? query.substr(start)
            : query.substr(start, amp - start);

        size_t eq = token.find('=');
        if (eq != std::string::npos)
        {
            std::string name = token.substr(0, eq);
            std::string value = token.substr(eq + 1);
            if (name == key)
                return value;
        }

        if (amp == std::string::npos)
            break;
        start = amp + 1;
    }

    return "";
}

std::string stripQueryString(const std::string& path)
{
    size_t question = path.find('?');
    if (question == std::string::npos)
        return path;
    return path.substr(0, question);
}
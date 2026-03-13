#ifndef SESSIONMANAGER_HPP
#define SESSIONMANAGER_HPP

#include "HttpReq.hpp"
#include <map>
#include <string>

class HttpResponse;

// Represents one browser session tracked by the server.
struct Session
{
    // True only after successful login flow.
    bool        logged_in;
    // Unique session identifier shared with browser as session_id cookie.
    std::string id;
    // Optional user value captured from /login?user=...
    std::string username;

    // Default starts as anonymous / not authenticated.
    Session() : logged_in(false), id(""), username("") {}
};

// Global in-memory session storage: key=session_id, value=Session data.
extern std::map<std::string, Session> sessions;

// Parse Cookie header and return session_id value ("" if absent).
std::string extractSessionId(const HttpRequest& req);
// Create a unique random session id string.
std::string generateSessionId();
// Create + insert a new session object and return reference to it.
Session& createSession();
// Validate that session_id exists in sessions map.
bool isSessionValid(const std::string& sessionId);
// Add Set-Cookie header to response for sending session_id to browser.
void attachSetCookieHeader(HttpResponse& res, const std::string& sessionId);

// Extract one query parameter from a URL path (e.g. user from /login?user=...)
std::string extractQueryParam(const std::string& path, const std::string& key);
// Remove query part from path (e.g. /login?user=x -> /login)
std::string stripQueryString(const std::string& path);

#endif
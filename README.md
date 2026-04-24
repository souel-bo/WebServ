*This project has been created as part of the 42 curriculum by <login1>, <login2>.*

# Webserv

## Description

Webserv is a custom HTTP server written in C++98, inspired by the behavior and architecture of NGINX. The goal of this project is to understand how a web server works internally by rebuilding its core features from scratch.

This project focuses on low-level networking, socket programming, HTTP request parsing, event-driven I/O, process management, and configuration handling. The server must be able to handle multiple client connections simultaneously while respecting the HTTP/1.1 protocol.

Main objectives of the project include:

- Building a fully functional HTTP server
- Managing multiple clients using non-blocking I/O
- Supporting GET, POST, and DELETE methods
- Handling file uploads
- Executing CGI scripts
- Parsing custom configuration files
- Managing routes, redirections, and error pages

This project provides practical experience with system programming and helps develop a deeper understanding of how modern web servers operate.

---

## Features

- C++98 compliant implementation
- Non-blocking sockets
- `epoll(epoll_create/epoll_ctl/epoll_wait)` for multiplexing
- HTTP/1.1 request handling
- GET, POST, DELETE methods
- Static file serving
- File upload support
- Large file support
- CGI execution (Python/PHP/BASH/...)
- Custom error pages
- Multiple server blocks
- Route configuration
- Client body size limits
- Autoindex support
- Redirections

---

## Instructions

### Compilation

Clone the repository and compile the project using `make`.

```bash
git clone <https://github.com/ACH4Q/WebServ.git>
cd webserv
make
./webserv config/websrv.conf
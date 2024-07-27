#ifndef SIPSERVER_H
#define SIPSERVER_H

#include "SIPMessage.h"
#include <string>
#include <netinet/in.h>

class SIPServer {
public:
    SIPServer(int port);
    void start();

private:
    void handle_request(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void send_response(const std::string& response, const struct sockaddr_in& client_addr);

    int server_fd;
    int port;
    struct sockaddr_in server_addr;
};

#endif // SIPSERVER_H


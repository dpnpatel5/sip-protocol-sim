#include "SIPServer.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

SIPServer::SIPServer(int port) : port(port) {
    // Create socket
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
}

void SIPServer::start() {
    char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    while (true) {
        ssize_t recv_len = recvfrom(server_fd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (recv_len < 0) {
            perror("recvfrom failed");
            continue;
        }

        buffer[recv_len] = '\0';
        std::string message(buffer);
        handle_request(message, client_addr);
    }
}

void SIPServer::handle_request(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    SIPMessage message;
    message.parse(raw_message);

    if (message.method == "INVITE") {
        send_response("SIP/2.0 200 OK\r\nContact: <sip:server@domain.com>\r\nContent-Length: 0\r\n\r\n", client_addr);
    } else if (message.method == "ACK") {
        send_response("SIP/2.0 200 OK\r\nContent-Length: 0\r\n\r\n", client_addr);
    } else if (message.method == "BYE") {
        send_response("SIP/2.0 200 OK\r\nContent-Length: 0\r\n\r\n", client_addr);
    } else if (message.method == "REGISTER") {
        send_response("SIP/2.0 200 OK\r\nContact: <sip:server@domain.com>\r\nExpires: 3600\r\nContent-Length: 0\r\n\r\n",client_addr);
    } else {
        send_response("SIP/2.0 405 Method Not Allowed\r\nContent-Length: 0\r\n\r\n", client_addr);
    }
}

void SIPServer::send_response(const std::string& response, const struct sockaddr_in& client_addr) {
    if (sendto(server_fd, response.c_str(), response.length(), 0, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
        perror("sendto failed");
    }
}


#include "SIPClient.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

SIPClient::SIPClient(const std::string& server_ip, int server_port)
    : server_ip(server_ip), server_port(server_port) {
    // Create socket
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
}

void SIPClient::send_message(const std::string& message) {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        perror("invalid address");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Send message
    ssize_t sent_len = sendto(client_fd, message.c_str(), message.length(), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (sent_len < 0) {
        perror("sendto failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    else{
       std::cout<<"Msg sent"<<" " <<message.c_str();
    }

    // Receive response
    char buffer[1024];
    struct sockaddr_in response_addr;
    socklen_t addr_len = sizeof(response_addr);
    ssize_t recv_len = recvfrom(client_fd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&response_addr, &addr_len);
    if (recv_len < 0) {
        perror("recvfrom failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    buffer[recv_len] = '\0';
    std::cout << "Received response: " << buffer << std::endl;

    close(client_fd);
}

std::string SIPClient::create_message(const std::string& method, const std::string& to, const std::string& from) {
    std::string message = method + " sip:" + to + " SIP/2.0\r\n"
                          "Via: SIP/2.0/UDP client.example.com;branch=z9hG4bK776asdhds\r\n"
                          "Max-Forwards: 70\r\n"
                          "To: <sip:" + to + ">\r\n"
                          "From: <sip:" + from + ">;tag=1928301774\r\n"
                          "Call-ID: a84b4c76e66710\r\n"
                          "CSeq: 1 " + method + "\r\n"
                          "Contact: <sip:" + from + ">\r\n"
                          "Content-Length: 0\r\n\r\n";
    return message;
}


#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "SIPServer.h"

SIPServer::SIPServer(const std::string& ip, int port) : ip_(ip), port_(port) {
    // Create socket
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    memset(&server_addr_, 0, sizeof(server_addr_));
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_addr.s_addr = inet_addr(ip_.c_str());
    server_addr_.sin_port = htons(port_);

    // Bind socket to address
    if (bind(sockfd_, (struct sockaddr*)&server_addr_, sizeof(server_addr_)) < 0) {
        perror("bind failed");
        close(sockfd_);
        exit(EXIT_FAILURE);
    }
}

void SIPServer::start() {
    char buffer[2048];
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    std::cout << "SIP Server listening on " << ip_ << ":" << port_ << std::endl;

    while (true) {
        ssize_t len = recvfrom(sockfd_, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client_addr, &client_addr_len);
        if (len < 0) {
            perror("recvfrom failed");
            continue;
        }

        buffer[len] = '\0';
        std::string raw_message(buffer);

	std::string method = get_method_from_sip_message(raw_message);
	std::cout << "Received SIP method: " << method << std::endl;

        process_message(method, raw_message, client_addr);
    }
}

void SIPServer::process_message(const std::string& method, const std::string& raw_message, const struct sockaddr_in& client_addr) {
    if (method == "REGISTER") {
        handle_register(raw_message, client_addr);
    } else if (method == "INVITE") {
        handle_invite(raw_message, client_addr);
    } else if (method == "ACK") {
        handle_ack(raw_message, client_addr);
    } else if (method == "BYE") {
        handle_bye(raw_message, client_addr);
    } else if (method == "CANCEL") {
        handle_cancel(raw_message, client_addr);
    } else if (method == "UPDATE") {
        handle_update(raw_message, client_addr);
    } else if (method == "REFER") {
        handle_refer(raw_message, client_addr);
    } else if (method == "PRACK") {
        handle_prack(raw_message, client_addr);
    } else if (method == "SUBSCRIBE") {
        handle_subscribe(raw_message, client_addr);
    } else if (method == "NOTIFY") {
        handle_notify(raw_message, client_addr);
    } else if (method == "PUBLISH") {
        handle_publish(raw_message, client_addr);
    } else if (method == "MESSAGE") {
        handle_message(raw_message, client_addr);
    } else if (method == "INFO") {
        handle_info(raw_message, client_addr);
    } else if (method == "OPTIONS") {
        handle_options(raw_message, client_addr);
    } else {
        std::cerr << "Unsupported SIP method: " << method << std::endl;
    }
}

void SIPServer::send_response(const std::string& response, const struct sockaddr_in& client_addr) {
    ssize_t sent_len = sendto(sockfd_, response.c_str(), response.length(), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
    if (sent_len < 0) {
        perror("sendto failed");
    }
}

void SIPServer::handle_register(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling REGISTER request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: REGISTER\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_invite(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling INVITE request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 180 Ringing)
    std::string response = "SIP/2.0 180 Ringing\r\n"
                           "CSeq: INVITE\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_ack(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling ACK request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: ACK\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_bye(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling BYE request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: BYE\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_cancel(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling CANCEL request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: CANCEL\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_update(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling UPDATE request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: UPDATE\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_refer(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling REFER request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: REFER\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_prack(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling PRACK request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: PRACK\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_subscribe(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling SUBSCRIBE request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: SUBSCRIBE\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_notify(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling NOTIFY request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: NOTIFY\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_publish(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling PUBLISH request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: PUBLISH\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_message(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling MESSAGE request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: MESSAGE\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_info(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling INFO request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: INFO\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}

void SIPServer::handle_options(const std::string& raw_message, const struct sockaddr_in& client_addr) {
    std::cout << "Handling OPTIONS request:\n" << raw_message << std::endl;
    // Construct and send response (e.g., 200 OK)
    std::string response = "SIP/2.0 200 OK\r\n"
                           "CSeq: OPTIONS\r\n"
                           "Content-Length: 0\r\n\r\n";
    send_response(response, client_addr);
}



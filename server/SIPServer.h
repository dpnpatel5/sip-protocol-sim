#ifndef SIPSERVER_H
#define SIPSERVER_H

#include <string>
#include <netinet/in.h>
#include "SIPParser.h"

class SIPServer {
public:
    SIPServer(const std::string& ip, int port);
    void start();
    
private:
    std::string ip_;
    int port_;
    int sockfd_;
    struct sockaddr_in server_addr_;

    void handle_request(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void process_message(const std::string& method, const std::string& raw_message, const struct sockaddr_in& client_addr);
    std::string get_message_header(const std::string& raw_message, const std::string& header_name);
    void send_response(const std::string& response, const struct sockaddr_in& client_addr);

    // Helper methods to handle specific SIP methods
    void handle_register(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_invite(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_ack(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_bye(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_cancel(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_update(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_refer(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_prack(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_subscribe(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_notify(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_publish(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_message(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_info(const std::string& raw_message, const struct sockaddr_in& client_addr);
    void handle_options(const std::string& raw_message, const struct sockaddr_in& client_addr);
};

#endif // SIPSERVER_H


#include "SIPClient.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

SIPClient::SIPClient(const std::string& server_ip, int server_port)
    : server_ip(server_ip), server_port(server_port) {
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

    ssize_t sent_len = sendto(client_fd, message.c_str(), message.length(), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (sent_len < 0) {
        perror("sendto failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

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

std::string SIPClient::common_headers(const std::string& to, const std::string& from, const std::string& call_id, const std::string& cseq_method, int cseq_number) {
    return "Via: SIP/2.0/UDP client.example.com;branch=z9hG4bK776asdhds\r\n"
           "Max-Forwards: 70\r\n"
           "To: <sip:" + to + ">\r\n"
           "From: <sip:" + from + ">;tag=1928301774\r\n"
           "Call-ID: " + call_id + "\r\n"
           "CSeq: " + std::to_string(cseq_number) + " " + cseq_method + "\r\n"
           "Contact: <sip:" + from + ">\r\n"
           "Allow: INVITE, ACK, OPTIONS, BYE, CANCEL, SUBSCRIBE, NOTIFY, REFER, MESSAGE, INFO, PING\r\n"
           "Content-Length: 0\r\n";
}

std::string SIPClient::create_invite(const std::string& to, const std::string& from) {
    std::string call_id = "a84b4c76e66710"; // Example Call-ID, should be unique per call
    return "INVITE sip:" + to + " SIP/2.0\r\n" +
           common_headers(to, from, call_id, "INVITE", 1) + "\r\n";
}

std::string SIPClient::create_ack(const std::string& to, const std::string& from, const std::string& call_id) {
    return "ACK sip:" + to + " SIP/2.0\r\n" +
           common_headers(to, from, call_id, "ACK", 2) + "\r\n";
}

std::string SIPClient::create_bye(const std::string& to, const std::string& from, const std::string& call_id) {
    return "BYE sip:" + to + " SIP/2.0\r\n" +
           common_headers(to, from, call_id, "BYE", 3) + "\r\n";
}

std::string SIPClient::create_register(const std::string& from, const std::string& contact, int expires) {
    std::string call_id = "b84b4c76e66711"; // Example Call-ID, should be unique per call
    return "REGISTER sip:example.com SIP/2.0\r\n"
           "Via: SIP/2.0/UDP client.example.com;branch=z9hG4bK776asdhds\r\n"
           "Max-Forwards: 70\r\n"
           "To: <sip:" + from + ">\r\n"
           "From: <sip:" + from + ">;tag=1928301774\r\n"
           "Call-ID: " + call_id + "\r\n"
           "CSeq: 1 REGISTER\r\n"
           "Contact: <sip:" + contact + ">\r\n"
           "Expires: " + std::to_string(expires) + "\r\n"
           "Allow: INVITE, ACK, OPTIONS, BYE, CANCEL, SUBSCRIBE, NOTIFY, REFER, MESSAGE, INFO, PING\r\n"
           "Content-Length: 0\r\n\r\n";
}

std::string SIPClient::create_cancel(const std::string& to, const std::string& from, const std::string& call_id) {
    return "CANCEL sip:" + to + " SIP/2.0\r\n" +
           common_headers(to, from, call_id, "CANCEL", 4) + "\r\n";
}

std::string SIPClient::create_update(const std::string& to, const std::string& from, const std::string& call_id) {
    return "UPDATE sip:" + to + " SIP/2.0\r\n" +
           common_headers(to, from, call_id, "UPDATE", 5) + "\r\n";
}

std::string SIPClient::create_refer(const std::string& to, const std::string& from, const std::string& refer_to) {
    std::string call_id = "c84b4c76e66712"; // Example Call-ID, should be unique per call
    return "REFER sip:" + to + " SIP/2.0\r\n"
           "Via: SIP/2.0/UDP client.example.com;branch=z9hG4bK776asdhds\r\n"
           "Max-Forwards: 70\r\n"
           "To: <sip:" + to + ">\r\n"
           "From: <sip:" + from + ">;tag=1928301774\r\n"
           "Call-ID: " + call_id + "\r\n"
           "CSeq: 1 REFER\r\n"
           "Refer-To: <sip:" + refer_to + ">\r\n"
           "Contact: <sip:" + from + ">\r\n"
           "Allow: INVITE, ACK, OPTIONS, BYE, CANCEL, SUBSCRIBE, NOTIFY, REFER, MESSAGE, INFO, PING\r\n"
           "Content-Length: 0\r\n\r\n";
}

std::string SIPClient::create_prack(const std::string& to, const std::string& from, const std::string& call_id) {
    return "PRACK sip:" + to + " SIP/2.0\r\n" +
           common_headers(to, from, call_id, "PRACK", 6) + "\r\n";
}

std::string SIPClient::create_subscribe(const std::string& to, const std::string& from, int expires) {
    std::string call_id = "d84b4c76e66713"; // Unique per call
    return "SUBSCRIBE sip:" + to + " SIP/2.0\r\n"
           "Via: SIP/2.0/UDP client.example.com;branch=z9hG4bK776asdhds\r\n"
           "Max-Forwards: 70\r\n"
           "To: <sip:" + to + ">\r\n"
           "From: <sip:" + from + ">;tag=1928301774\r\n"
           "Call-ID: " + call_id + "\r\n"
           "CSeq: 1 SUBSCRIBE\r\n"
           "Expires: " + std::to_string(expires) + "\r\n"
           "Contact: <sip:" + from + ">\r\n"
           "Allow: INVITE, ACK, OPTIONS, BYE, CANCEL, SUBSCRIBE, NOTIFY, REFER, MESSAGE, INFO, PING\r\n"
           "Content-Length: 0\r\n\r\n";
}

std::string SIPClient::create_notify(const std::string& to, const std::string& from, const std::string& event) {
    std::string call_id = "e84b4c76e66714"; // Unique per call
    return "NOTIFY sip:" + to + " SIP/2.0\r\n"
           "Via: SIP/2.0/UDP client.example.com;branch=z9hG4bK776asdhds\r\n"
           "Max-Forwards: 70\r\n"
           "To: <sip:" + to + ">\r\n"
           "From: <sip:" + from + ">;tag=1928301774\r\n"
           "Call-ID: " + call_id + "\r\n"
           "CSeq: 1 NOTIFY\r\n"
           "Event: " + event + "\r\n"
           "Contact: <sip:" + from + ">\r\n"
           "Allow: INVITE, ACK, OPTIONS, BYE, CANCEL, SUBSCRIBE, NOTIFY, REFER, MESSAGE, INFO, PING\r\n"
           "Content-Length: 0\r\n\r\n";
}

std::string SIPClient::create_publish(const std::string& from, const std::string& event) {
    std::string call_id = "f84b4c76e66715"; // Unique per call
    return "PUBLISH sip:example.com SIP/2.0\r\n"
           "Via: SIP/2.0/UDP client.example.com;branch=z9hG4bK776asdhds\r\n"
           "Max-Forwards: 70\r\n"
           "To: <sip:example.com>\r\n"
           "From: <sip:" + from + ">;tag=1928301774\r\n"
           "Call-ID: " + call_id + "\r\n"
           "CSeq: 1 PUBLISH\r\n"
           "Event: " + event + "\r\n"
           "Contact: <sip:" + from + ">\r\n"
           "Allow: INVITE, ACK, OPTIONS, BYE, CANCEL, SUBSCRIBE, NOTIFY, REFER, MESSAGE, INFO, PING\r\n"
           "Content-Length: 0\r\n\r\n";
}

std::string SIPClient::create_message(const std::string& to, const std::string& from, const std::string& content) {
    std::string call_id = "g84b4c76e66716"; // Unique per call
    return "MESSAGE sip:" + to + " SIP/2.0\r\n"
           "Via: SIP/2.0/UDP client.example.com;branch=z9hG4bK776asdhds\r\n"
           "Max-Forwards: 70\r\n"
           "To: <sip:" + to + ">\r\n"
           "From: <sip:" + from + ">;tag=1928301774\r\n"
           "Call-ID: " + call_id + "\r\n"
           "CSeq: 1 MESSAGE\r\n"
           "Content-Type: text/plain\r\n"
           "Content-Length: " + std::to_string(content.length()) + "\r\n"
           "Allow: INVITE, ACK, OPTIONS, BYE, CANCEL, SUBSCRIBE, NOTIFY, REFER, MESSAGE, INFO, PING\r\n"
           "\r\n" +
           content;
}

std::string SIPClient::create_info(const std::string& to, const std::string& from, const std::string& content_type) {
    std::string call_id = "h84b4c76e66717"; // Unique per call
    return "INFO sip:" + to + " SIP/2.0\r\n"
           "Via: SIP/2.0/UDP client.example.com;branch=z9hG4bK776asdhds\r\n"
           "Max-Forwards: 70\r\n"
           "To: <sip:" + to + ">\r\n"
           "From: <sip:" + from + ">;tag=1928301774\r\n"
           "Call-ID: " + call_id + "\r\n"
           "CSeq: 1 INFO\r\n"
           "Content-Type: " + content_type + "\r\n"
           "Content-Length: 0\r\n"
           "Allow: INVITE, ACK, OPTIONS, BYE, CANCEL, SUBSCRIBE, NOTIFY, REFER, MESSAGE, INFO, PING\r\n"
           "\r\n";
}

std::string SIPClient::create_options(const std::string& to, const std::string& from) {
    std::string call_id = "i84b4c76e66718"; // Unique per call
    return "OPTIONS sip:" + to + " SIP/2.0\r\n"
           "Via: SIP/2.0/UDP client.example.com;branch=z9hG4bK776asdhds\r\n"
           "Max-Forwards: 70\r\n"
           "To: <sip:" + to + ">\r\n"
           "From: <sip:" + from + ">;tag=1928301774\r\n"
           "Call-ID: " + call_id + "\r\n"
           "CSeq: 1 OPTIONS\r\n"
           "Content-Length: 0\r\n"
           "Allow: INVITE, ACK, OPTIONS, BYE, CANCEL, SUBSCRIBE, NOTIFY, REFER, MESSAGE, INFO, PING\r\n"
           "\r\n";
}



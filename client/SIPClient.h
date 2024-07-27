#ifndef SIPCLIENT_H
#define SIPCLIENT_H

#include <string>

class SIPClient {
public:
    SIPClient(const std::string& server_ip, int server_port);
    void send_message(const std::string& message);

    std::string create_invite(const std::string& to, const std::string& from);
    std::string create_ack(const std::string& to, const std::string& from, const std::string& call_id);
    std::string create_bye(const std::string& to, const std::string& from, const std::string& call_id);
    std::string create_register(const std::string& from, const std::string& contact, int expires);
    std::string create_cancel(const std::string& to, const std::string& from, const std::string& call_id);
    std::string create_update(const std::string& to, const std::string& from, const std::string& call_id);
    std::string create_refer(const std::string& to, const std::string& from, const std::string& refer_to);
    std::string create_prack(const std::string& to, const std::string& from, const std::string& call_id);
    std::string create_subscribe(const std::string& to, const std::string& from, int expires);
    std::string create_notify(const std::string& to, const std::string& from, const std::string& event);
    std::string create_publish(const std::string& from, const std::string& event);
    std::string create_message(const std::string& to, const std::string& from, const std::string& content);
    std::string create_info(const std::string& to, const std::string& from, const std::string& content_type);
    std::string create_options(const std::string& to, const std::string& from);

private:
    std::string server_ip;
    int server_port;
    int client_fd;

    std::string common_headers(const std::string& to, const std::string& from, const std::string& call_id, const std::string& cseq_method, int cseq_number);
};

#endif // SIPCLIENT_H


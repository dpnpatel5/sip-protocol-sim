#ifndef SIPCLIENT_H
#define SIPCLIENT_H

#include <string>

class SIPClient {
public:
    SIPClient(const std::string& server_ip, int server_port);
    void send_message(const std::string& message);
    std::string create_message(const std::string& method, const std::string& to, const std::string& from);

private:
    std::string server_ip;
    int server_port;
    int client_fd;
};

#endif // SIPCLIENT_H


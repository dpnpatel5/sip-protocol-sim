#ifndef SIPMESSAGE_H
#define SIPMESSAGE_H

#include <string>
#include <map>
#include <vector>

class SIPMessage {
public:
    SIPMessage(const std::string& raw_message);

    std::string get_method() const;
    std::string get_header(const std::string& header_name) const;
    std::string get_body() const;
    std::map<std::string, std::string> get_all_headers() const;

private:
    void parse_message(const std::string& raw_message);

    std::string method;
    std::map<std::string, std::string> headers;
    std::string body;
};

#endif // SIPMESSAGE_H


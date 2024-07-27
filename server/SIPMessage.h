#ifndef SIPMESSAGE_H
#define SIPMESSAGE_H

#include <string>
#include <map>

class SIPMessage {
public:
    std::string method;
    std::string uri;
    std::map<std::string, std::string> headers;
    std::string body;

    void parse(const std::string& raw_message);
    std::string to_string() const;

private:
    void parse_headers(const std::string& header_section);
};

#endif // SIPMESSAGE_H


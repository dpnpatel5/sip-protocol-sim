#include "SIPMessage.h"
#include <sstream>

void SIPMessage::parse(const std::string& raw_message) {
    size_t method_end = raw_message.find(' ');
    method = raw_message.substr(0, method_end);

    size_t uri_start = method_end + 1;
    size_t uri_end = raw_message.find(' ', uri_start);
    uri = raw_message.substr(uri_start, uri_end - uri_start);

    size_t headers_start = raw_message.find("\r\n") + 2;
    size_t body_start = raw_message.find("\r\n\r\n") + 4;
    body = raw_message.substr(body_start);

    parse_headers(raw_message.substr(headers_start, body_start - headers_start - 4));
}

void SIPMessage::parse_headers(const std::string& header_section) {
    size_t pos = 0;
    while (pos < header_section.length()) {
        size_t header_end = header_section.find("\r\n", pos);
        if (header_end == std::string::npos) break;

        std::string header_line = header_section.substr(pos, header_end - pos);
        size_t colon_pos = header_line.find(':');
        if (colon_pos != std::string::npos) {
            std::string header_name = header_line.substr(0, colon_pos);
            std::string header_value = header_line.substr(colon_pos + 2);
            headers[header_name] = header_value;
        }
        pos = header_end + 2;
    }
}

std::string SIPMessage::to_string() const {
    std::string result = method + " " + uri + " SIP/2.0\r\n";
    for (const auto& header : headers) {
        result += header.first + ": " + header.second + "\r\n";
    }
    result += "\r\n" + body;
    return result;
}


#include "SIPMessage.h"
#include <sstream>
#include <algorithm>
#include <cctype>

SIPMessage::SIPMessage(const std::string& raw_message) {
    parse_message(raw_message);
}

void SIPMessage::parse_message(const std::string& raw_message) {
    std::istringstream stream(raw_message);
    std::string line;
    bool headers_done = false;

    while (std::getline(stream, line)) {
        // Check for empty line indicating end of headers
        if (line.empty()) {
            headers_done = true;
            continue;
        }

        if (!headers_done) {
            // Parse headers
            size_t colon_pos = line.find("sip");
            if (colon_pos != std::string::npos) {
                std::string header_name = line.substr(0, colon_pos);
                std::string header_value = line.substr(colon_pos + 1);
                // Trim header_value
                header_value.erase(header_value.find_last_not_of(" \t\r\n") + 1);
                // Convert header_name to lowercase
                //std::transform(header_name.begin(), header_name.end(), header_name.begin(), ::tolower);
                headers[header_name] = header_value;

                if (method.empty()) {
                    // Assuming the method is in the first line of the message
                    method = header_name;
                }
            }
        } else {
            // Parse body
            body += line + "\n";
        }
    }

    // Remove the trailing newline character from the body
    if (!body.empty()) {
        body.pop_back();
    }
}

std::string SIPMessage::get_method() const {
    return method;
}

std::string SIPMessage::get_header(const std::string& header_name) const {
    std::string header_name_lower = header_name;
    std::transform(header_name_lower.begin(), header_name_lower.end(), header_name_lower.begin(), ::tolower);
    auto it = headers.find(header_name_lower);
    return (it != headers.end()) ? it->second : "";
}

std::string SIPMessage::get_body() const {
    return body;
}

std::map<std::string, std::string> SIPMessage::get_all_headers() const {
    return headers;
}


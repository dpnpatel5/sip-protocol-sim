#include "SIPServer.h"
#include <iostream>
#include <cstdlib> // For std::stoi
#include <cstring> // For std::strlen

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP> <Port>" << std::endl;
        return 1;
    }

    std::string server_ip = argv[1];
    int server_port;

    try {
        server_port = std::stoi(argv[2]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid port number. Port must be an integer." << std::endl;
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "Port number out of range." << std::endl;
        return 1;
    }

    // Create SIP server
    SIPServer server(server_ip, server_port);

    // Start the server
    std::cout << "Starting SIP server on " << server_ip << ":" << server_port << std::endl;
    server.start();

    return 0;
}


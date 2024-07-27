#include "SIPClient.h"
#include <iostream>
#include <string>

int main() {
    // Server IP and port (update as necessary)
    std::string server_ip = "127.0.0.1"; // Localhost or server IP
    int server_port = 5060; // SIP port

    // Create SIP client
    SIPClient client(server_ip, server_port);

    // User input loop
    while (true) {
        std::string method, to, from;

        std::cout << "Enter SIP method (INVITE, ACK, BYE, etc.) or 'quit' to exit: ";
        std::getline(std::cin, method);

        if (method == "quit") {
            break;
        }

        std::cout << "Enter 'To' address (e.g., user@domain.com): ";
        std::getline(std::cin, to);

        std::cout << "Enter 'From' address (e.g., user@domain.com): ";
        std::getline(std::cin, from);

        // Create and send SIP message
        std::string message = client.create_message(method, to, from);
        client.send_message(message);
    }

    return 0;
}


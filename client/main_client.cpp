#include "SIPClient.h"
#include <iostream>
#include <cstdlib>
#include <limits>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <Server IP> <Server Port>" << std::endl;
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

    // Create SIP client
    SIPClient client(server_ip, server_port);

    // User input loop
    while (true) {
        std::string method;
        std::cout << "Enter SIP method (REGISTER, INVITE, ACK, BYE, CANCEL, UPDATE, REFER, PRACK, SUBSCRIBE, NOTIFY, PUBLISH, MESSAGE, INFO, OPTIONS) or 'quit' to exit: ";
        std::getline(std::cin, method);

        if (method == "quit") {
            break;
        }

        std::string to, from, call_id, contact, refer_to, event, content, content_type;
        int expires;

        if (method == "INVITE" || method == "ACK" || method == "BYE" || method == "CANCEL" || method == "UPDATE" || method == "PRACK" || method == "OPTIONS") {
            std::cout << "Enter 'To' address (e.g., user@domain.com): ";
            std::getline(std::cin, to);
            std::cout << "Enter 'From' address (e.g., user@domain.com): ";
            std::getline(std::cin, from);
            if (method == "ACK" || method == "BYE" || method == "CANCEL" || method == "UPDATE" || method == "PRACK") {
                std::cout << "Enter Call-ID: ";
                std::getline(std::cin, call_id);
            }
        } else if (method == "REGISTER") {
            std::cout << "Enter 'From' address (e.g., user@domain.com): ";
            std::getline(std::cin, from);
            std::cout << "Enter Contact address (e.g., user@client.com): ";
            std::getline(std::cin, contact);
            std::cout << "Enter expiration time (in seconds): ";
            std::cin >> expires;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if (method == "REFER") {
            std::cout << "Enter 'To' address (e.g., user@domain.com): ";
            std::getline(std::cin, to);
            std::cout << "Enter 'From' address (e.g., user@domain.com): ";
            std::getline(std::cin, from);
            std::cout << "Enter 'Refer-To' address (e.g., user@otherdomain.com): ";
            std::getline(std::cin, refer_to);
        } else if (method == "SUBSCRIBE") {
            std::cout << "Enter 'To' address (e.g., user@domain.com): ";
            std::getline(std::cin, to);
            std::cout << "Enter 'From' address (e.g., user@domain.com): ";
            std::getline(std::cin, from);
            std::cout << "Enter expiration time (in seconds): ";
            std::cin >> expires;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if (method == "NOTIFY") {
            std::cout << "Enter 'To' address (e.g., user@domain.com): ";
            std::getline(std::cin, to);
            std::cout << "Enter 'From' address (e.g., user@domain.com): ";
            std::getline(std::cin, from);
            std::cout << "Enter 'Event' (e.g., message-summary): ";
            std::getline(std::cin, event);
        } else if (method == "PUBLISH") {
            std::cout << "Enter 'From' address (e.g., user@domain.com): ";
            std::getline(std::cin, from);
            std::cout << "Enter 'Event' (e.g., presence:online): ";
            std::getline(std::cin, event);
        } else if (method == "MESSAGE") {
            std::cout << "Enter 'To' address (e.g., user@domain.com): ";
            std::getline(std::cin, to);
            std::cout << "Enter 'From' address (e.g., user@domain.com): ";
            std::getline(std::cin, from);
            std::cout << "Enter message content: ";
            std::getline(std::cin, content);
            std::cout << "Enter Content-Type (e.g., text/plain): ";
            std::getline(std::cin, content_type);
        } else if (method == "INFO") {
            std::cout << "Enter 'To' address (e.g., user@domain.com): ";
            std::getline(std::cin, to);
            std::cout << "Enter 'From' address (e.g., user@domain.com): ";
            std::getline(std::cin, from);
            std::cout << "Enter Content-Type (e.g., application/sdp): ";
            std::getline(std::cin, content_type);
        } else {
            std::cout << "Unknown SIP method. Please try again.\n";
            continue;
        }

        std::string message;
        if (method == "REGISTER") {
            message = client.create_register(from, contact, expires);
        } else if (method == "INVITE") {
            message = client.create_invite(to, from);
        } else if (method == "ACK") {
            message = client.create_ack(to, from, call_id);
        } else if (method == "BYE") {
            message = client.create_bye(to, from, call_id);
        } else if (method == "CANCEL") {
            message = client.create_cancel(to, from, call_id);
        } else if (method == "UPDATE") {
            message = client.create_update(to, from, call_id);
        } else if (method == "REFER") {
            message = client.create_refer(to, from, refer_to);
        } else if (method == "PRACK") {
            message = client.create_prack(to, from, call_id);
        } else if (method == "SUBSCRIBE") {
            message = client.create_subscribe(to, from, expires);
        } else if (method == "NOTIFY") {
            message = client.create_notify(to, from, event);
        } else if (method == "PUBLISH") {
            message = client.create_publish(from, event);
        } else if (method == "MESSAGE") {
            message = client.create_message(to, from, content);
        } else if (method == "INFO") {
            message = client.create_info(to, from, content_type);
        } else if (method == "OPTIONS") {
            message = client.create_options(to, from);
        }

        // Send the SIP message
        client.send_message(message);
    }

    return 0;
}


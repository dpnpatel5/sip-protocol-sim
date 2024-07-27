#include "SIPServer.h"
#include <iostream>

int main() {
    try {
        SIPServer server(5060); // SIP typically uses port 5060
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}


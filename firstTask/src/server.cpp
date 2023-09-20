#include <iostream>
#include "Connection.hpp"

int main() {
    Connection server;

    // Initialize the server to listen on port 5577
    if (server.InitializeServer("5577")) {
        std::cout << "Server is listening on port 5577. Waiting for messages..." << std::endl;

        if (server.AcceptConnection()) {
            char buffer[DEFAULT_BUFLEN];
            while (server.Receive(buffer, sizeof(buffer))) {
                std::cout << "Received from client: " << buffer << std::endl;
            }
        } else {
            std::cerr << "Failed to accept client connection." << std::endl;
        }
        server.Close();
    } else {
        std::cerr << "Failed to initialize server." << std::endl;
    }
    return 0;
}

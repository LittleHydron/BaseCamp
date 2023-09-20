#include <iostream>
#include "Connection.hpp"

#define PORT "5577"
#define MESSAGE_LENGTH 8

int main() {
    Connection server;
    if (server.InitializeServer(PORT)) {
        std::cout << "Server is listening on port " <<  atoi(PORT) << ". Waiting for messages..." << std::endl;

        if (server.AcceptConnection()) {
            char message[DEFAULT_BUFLEN];
            while (server.Receive(message, sizeof(message))) {
                std::cout << message << std::endl;
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

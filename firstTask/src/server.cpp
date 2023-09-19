#include <iostream>
#include <boost/asio.hpp>
#include "Connection.hpp"

int main(void) {
    Connection connection(5577);
    std::cout << "Server listening on port 5577..." << std::endl;

    while (true) {
        std::string received;
        try {
            received = connection.receive();
        } catch (boost::system::system_error &error) {
            std::cout << error.what() << std::endl;
            break;
        }

        std::cout << "Received: " << received << std::endl;
    }

    return 0;
}

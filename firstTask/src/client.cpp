#include <iostream>
#include <tuple>
#include <thread>
#include <chrono>
#include "Connection.hpp"
#include "TrackMouse.hpp"

#define IP "127.0.0.1"
#define PORT "5577"
#define MESSAGE_LENGTH 8
#define SLEEP_TIME 2

int main() {
    Connection client;
    int lastX = 0, lastY = 0, x, y;
    if (client.Initialize(IP, PORT)) {
        char message[MESSAGE_LENGTH];
        bool sent;
        do {
            std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
            std::tie(x, y) = getMouseCoordinates();
            if (x == lastX && y == lastY) {
                sent = client.Send("Passive");
            } else {
                sent = client.Send("Active");
            }
            lastX = x, lastY = y;
        } while(sent);
        client.Close();
    } else {
        std::cerr << "Failed to initialize client." << std::endl;
    }

    return 0;
}

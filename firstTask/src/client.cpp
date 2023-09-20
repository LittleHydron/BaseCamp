#include <iostream>
#include <tuple>
#include <thread>
#include <chrono>
#include "Connection.hpp"
#include "TrackMouse.hpp"

int main() {
    Connection client;
    int lastX = 0, lastY = 0, x, y;
    if (client.Initialize("127.0.0.1", "5577")) {
        char message[8];
        bool sent;
        do {
            std::this_thread::sleep_for(std::chrono::seconds(2));
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

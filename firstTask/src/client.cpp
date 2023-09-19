#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <X11/Xlib.h>
#include "Connection.hpp"

using namespace boost::asio;

std::tuple <int,int> getMouseStatus(void) {
    Display* display = XOpenDisplay(NULL);
    if (display == nullptr) {
        std::cerr << "Error opening X Display" << std::endl;
        return {-1, -1};
    }

    XEvent event;
    XQueryPointer(display, DefaultRootWindow(display), &event.xbutton.root,
                  &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root,
                  &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    int x = event.xbutton.x_root;
    int y = event.xbutton.y_root;
    XCloseDisplay(display);
    return {x, y};
}

int main() {
    Connection connection("127.0.0.1", "5577");

    int lastX = 0;
    int lastY = 0;

    while (true) {
        auto [x, y] = getMouseStatus();
        try {
            if (x == lastX && y == lastY) {
                connection.send("Passive");
            } else {
                connection.send("Active");
            }
        } catch (boost::system::system_error &error) {
            std::cout << error.what() << std::endl;
        }
        lastX = x, lastY = y;
        connection.wait_for(2);
    }
    return 0;
}

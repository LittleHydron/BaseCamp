#include "TrackMouse.hpp"

#ifdef _WIN32
#include <windows.h>

std::tuple <int,int> getMouseCoordinates(void) {
    POINT cursorPos;
    std::tuple<int,int> position{-1, -1};
    if (GetCursorPos(&cursorPos)) {
        position = {cursorPos.x, cursorPos.y};
    } else {
        std::cerr << "Failed to get mouse coordinates." << std::endl;
    }
    return position;
}

#else
#include <X11/Xlib.h>

std::tuple <int,int> getMouseCoordinates(void) {
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

#endif
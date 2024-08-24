#include "includes/input.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <iostream>

namespace Input {

    std::pair<int, int> getMousePosition() {
        Display* display = XOpenDisplay(nullptr);
        if (display == nullptr) {
            std::cerr << "Unable to open X display\n";
            return {-1, -1};
        }

        Window root = DefaultRootWindow(display);
        int rootX, rootY, winX, winY;
        unsigned int mask;
        Window child, rootReturn;

        XQueryPointer(display, root, &rootReturn, &child, &rootX, &rootY, &winX, &winY, &mask);

        XCloseDisplay(display);
        return {rootX, rootY};
    }

    std::pair<std::pair<int, int>, std::pair<int, int>> captureArea() {
        std::pair<int, int> start, end;

        std::cout << "Click the first point...\n";
        std::cin.get();  // Wait for Enter key to simulate click
        start = getMousePosition();

        std::cout << "Click the second point...\n";
        std::cin.get();  // Wait for Enter key to simulate click
        end = getMousePosition();

        return {start, end};
    }
}


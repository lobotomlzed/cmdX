#ifndef INPUT_H
#define INPUT_H

#include <utility> // for std::pair

namespace Input {
    std::pair<int, int> getMousePosition();
    std::pair<std::pair<int, int>, std::pair<int, int>> captureArea();
}

#endif


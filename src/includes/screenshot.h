#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <string>
#include <utility>

namespace Screenshot {
    enum class Mode {
        FullScreen,
        AreaSelection
    };

    std::string capture(Mode mode = Mode::FullScreen);
    std::string captureArea(const std::pair<std::pair<int, int>, std::pair<int, int>>& area);
}

#endif

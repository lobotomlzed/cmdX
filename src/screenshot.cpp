#include "includes/screenshot.h"
#include "includes/input.h"
#include <ctime>
#include <sstream>
#include <cstdlib>

namespace Screenshot {
    std::string getCurrentDateTime() {
        std::time_t now = std::time(nullptr);
        std::tm *ltm = std::localtime(&now);
        std::ostringstream oss;
        oss << 1900 + ltm->tm_year
            << (ltm->tm_mon + 1)
            << ltm->tm_mday
            << ltm->tm_hour
            << ltm->tm_min
            << ltm->tm_sec;
        return oss.str();
    }

    std::string capture(Mode mode) {
        std::string dateTime = getCurrentDateTime();
        std::string fileName = "screenshot" + dateTime + ".png";

        if (mode == Mode::AreaSelection) {
            auto area = Input::captureArea();
            return captureArea(area);
        } else {
            std::string command = "scrot " + fileName;
            std::system(command.c_str());
        }

        return fileName;
    }

    std::string captureArea(const std::pair<std::pair<int, int>, std::pair<int, int>>& area) {
        std::string dateTime = getCurrentDateTime();
        std::string fileName = "screenshot" + dateTime + ".png";

        int x = std::min(area.first.first, area.second.first);
        int y = std::min(area.first.second, area.second.second);
        int width = std::abs(area.second.first - area.first.first);
        int height = std::abs(area.second.second - area.first.second);

        std::ostringstream oss;
        oss << "scrot -a " << x << "," << y << "," << width << "," << height << " " << fileName;
        std::system(oss.str().c_str());

        return fileName;
    }
}


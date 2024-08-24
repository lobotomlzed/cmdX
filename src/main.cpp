
#include "includes/screenshot.h"
#include "includes/upload.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Screenshot::Mode mode = Screenshot::Mode::FullScreen;

    if (argc > 2) {
        if (std::string(argv[2]) == "area") {
            mode = Screenshot::Mode::AreaSelection;
        }
    }

    std::string screenshotPath = Screenshot::capture(mode);
    
    if (argc >= 2) {
        std::string configPath = argv[1];
        std::string link = Upload::uploadFile(configPath, screenshotPath);
        if (!link.empty()) {
            std::cout << "File uploaded. Link: " << link << "\n";
        } else {
            std::cout << "Upload failed.\n";
        }
    } else {
        std::cout << "Screenshot saved as " << screenshotPath << "\n";
    }

    return 0;
}

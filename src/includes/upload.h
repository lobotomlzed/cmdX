#ifndef UPLOAD_H
#define UPLOAD_H

#include <string>

namespace Upload {
    std::string uploadFile(const std::string& configPath, const std::string& filePath);
}

#endif


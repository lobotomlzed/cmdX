#ifndef UPLOAD_H
#define UPLOAD_H

#include <string>

namespace Upload {
    bool uploadFile(const std::string& uploadUrl, const std::string& filePath);
}

#endif // UPLOAD_H


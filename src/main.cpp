
#include "includes/upload.h"
#include <curl/curl.h>
#include <iostream>

namespace Upload {

    bool uploadFile(const std::string& uploadUrl, const std::string& filePath) {
        CURL* curl;
        CURLcode res;
        bool success = false;

        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (curl) {
            curl_mime* mime = curl_mime_init(curl);
            curl_mimepart* part = curl_mime_addpart(mime);
            curl_mime_name(part, "file");
            curl_mime_filedata(part, filePath.c_str());

            curl_easy_setopt(curl, CURLOPT_URL, uploadUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

            res = curl_easy_perform(curl);
            if (res == CURLE_OK) {
                success = true;
            } else {
                std::cerr << "Upload failed: " << curl_easy_strerror(res) << "\n";
            }

            curl_mime_free(mime);
            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();
        return success;
    }
}


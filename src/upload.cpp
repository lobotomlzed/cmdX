#include "includes/upload.h"
#include <curl/curl.h>
#include <fstream>
#include <sstream>
#include <json/json.h>

namespace Upload {

    std::string parseConfig(const std::string& configPath) {
        std::ifstream configFile(configPath);
        std::ostringstream configStream;
        configStream << configFile.rdbuf();
        return configStream.str();
    }

    size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
        size_t totalSize = size * nmemb;
        s->append((char*)contents, totalSize);
        return totalSize;
    }

    std::string extractLink(const std::string& jsonResponse, const std::string& linkKey) {
        Json::Value root;
        Json::CharReaderBuilder builder;
        std::string errs;

        std::istringstream iss(jsonResponse);
        std::string link = "";

        if (Json::parseFromStream(builder, iss, &root, &errs)) {
            if (root.isMember(linkKey)) {
                link = root[linkKey].asString();
            }
        }
        return link;
    }

    std::string uploadFile(const std::string& configPath, const std::string& filePath) {
        std::string configContent = parseConfig(configPath);
        std::string requestURL, fileFormName, linkKey;

        Json::Value configJson;
        Json::CharReaderBuilder reader;
        std::string errs;

        std::istringstream configStream(configContent);
        Json::parseFromStream(reader, configStream, &configJson, &errs);

        requestURL = configJson["RequestURL"].asString();
        fileFormName = configJson["FileFormName"].asString();
        linkKey = configJson["URL"].asString();
        linkKey = linkKey.substr(6, linkKey.size() - 7);

        CURL *curl;
        CURLcode res;
        std::string responseStr;

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();

        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, requestURL.c_str());
            curl_mime *mime = curl_mime_init(curl);
            curl_mimepart *part = curl_mime_addpart(mime);

            curl_mime_name(part, fileFormName.c_str());
            curl_mime_filedata(part, filePath.c_str());
            curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStr);

            res = curl_easy_perform(curl);
            curl_mime_free(mime);
            curl_easy_cleanup(curl);

            if(res == CURLE_OK) {
                std::string link = extractLink(responseStr, linkKey);
                curl_global_cleanup();
                return link;
            }
        }

        curl_global_cleanup();
        return "";
    }
}


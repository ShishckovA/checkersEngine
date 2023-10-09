//
// Created by Alexey Shishkov on 08.10.2023.
//

#include "Requests.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void checkAndThrowErr(bool condition, const std::string &text) {
    if (!condition) {
        throw std::runtime_error(text);
    }
}


std::string Requests::get(const std::string &url, int maxRetry, int sleepTimeout) {
    CURLcode result_code;
    long http_code;
    CURL* session = curl_easy_init();
    std::string readBuffer;
    if (session) {
        for (int tryNum = 1; tryNum != maxRetry; ++tryNum) {
            try {
                curl_easy_setopt(session, CURLOPT_URL, url.c_str());
                curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(session, CURLOPT_WRITEDATA, &readBuffer);
                result_code = curl_easy_perform(session);
                checkAndThrowErr(result_code == CURLE_OK, "Request failed!");
                curl_easy_getinfo(session, CURLINFO_RESPONSE_CODE, &http_code);
                checkAndThrowErr(http_code == 200, "Bad result code: " + std::to_string(http_code));
                break;
            } catch (const std::runtime_error &err) {
                std::cerr << err.what() << std::endl;
                std::cerr << "Sleeping for " << sleepTimeout << " seconds..." << std::endl;
                std::chrono::milliseconds timespan(2000);
                std::this_thread::sleep_for(timespan);
                continue;
            }
        }
        curl_easy_cleanup(session);
        return readBuffer;
    }
    return "";
}
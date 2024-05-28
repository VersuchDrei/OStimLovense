#include "Request.h"

#include <curl/curl.h>

#include "Lovense/ErrorCode.h"
#include "Settings/SettingTable.h"
#include "Util/StringUtil.h"

namespace Request {
    size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string *)userp)->append((char *)contents, size * nmemb);
        return size * nmemb;
    }

    RequestResult send(std::string& toy, Lovense::CommandType &command, std::unordered_map<std::string, std::string> params) {
        Settings::SettingTable *settings = Settings::SettingTable::getSingleton();

        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        /* get a curl handle */
        curl = curl_easy_init();
        if (curl) {
            /* First set the URL that is about to receive our POST. This URL can
               just as well be a https:// URL if that is what should receive the
               data. */
            std::string url = "https://" + *settings->getDomain() + ":" + *settings->getPort() + "/command";
            logger::info("url: {}", url);
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            /* headers */
            struct curl_slist *slist1 = NULL;
            slist1 = curl_slist_append(slist1, "Content-Type: application/json");
            slist1 = curl_slist_append(slist1, "X-platform: OStim Standalone");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);

            /* Now specify the POST data */
            json post = json::object();
            post["command"] = command.command;
            for (auto &[key, value] : params) {
                if (StringUtil::isNumber(value)) {
                    post[key] = std::stoi(value);
                } else {
                    post[key] = value;
                }
            }
            if (!toy.empty()) {
                post["toy"] = toy;
            }
            post["apiVer"] = command.apiVer;
            std::string postStr = post.dump();
            logger::info("post: {}", postStr);
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postStr.c_str());

            /* set callback */
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            /* set additional options */
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

            /* Perform the request, res will get the return code */
            res = curl_easy_perform(curl);

            /* always cleanup */
            curl_slist_free_all(slist1);
            curl_easy_cleanup(curl);
        } else {
            logger::error("curl_easy_init() failed");
            return {RequestResultType::CURL_ERROR, json::object()};
        }

        /* Check for errors */
        if (res != CURLE_OK) {
            logger::error("curl_easy_perform() failed: {}", curl_easy_strerror(res));
            return {RequestResultType::CURL_ERROR, json::object()};
        }

        json result = json::parse(readBuffer, nullptr, false);
        if (result.is_discarded()) {
            logger::error("url request '{}' did not return a json: {}", command.command, readBuffer);
            return {RequestResultType::LOVENSE_ERROR, json::object()};
        }

        if (!result.contains("code")) {
            logger::error("url request '{}' return does not contain property 'code'", command.command);
            return {RequestResultType::LOVENSE_ERROR, result};
        }

        if (!result["code"].is_number_integer()) {
            logger::error("property 'code' of url request '{}' return is not a number", command.command);
            return {RequestResultType::LOVENSE_ERROR, result};
        }

        Lovense::ErrorCode code = result["code"];
        if (code != Lovense::ErrorCode::SUCCESS) {
            logger::error("url  request '{}' returned error code {}: {}", command.command, (int)code, Lovense::ErrorCodeAPI::getMessage(code));
            return {RequestResultType::LOVENSE_ERROR, result};
        }

        logger::info("url response: {}", result.dump());

        return {RequestResultType::SUCCESS, result};
    }
}
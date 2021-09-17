#include "PageLoader.hpp"
#include <iostream>
#include <curl/curl.h>


Page PageLoader::load(const std::string& url, std::string& domain)
{
    CURL* curl = curl_easy_init();

    std::string bodyResult{};
    std::string contentType{};
    std::string effectiveUrl{};
    char* contentType_c = NULL;
    int status;
    char* effectiveUrl_c = NULL;
    

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &bodyResult);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        
        CURLcode curlcode = curl_easy_perform(curl);

        if(curlcode == CURLE_OK)
        {
            curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &status);
            curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &effectiveUrl_c);
            curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &contentType_c);
    
            contentType=contentType_c;
            effectiveUrl=effectiveUrl_c;
        }
        curl_easy_cleanup(curl);
    }
    if(contentType.find("html") == std::string::npos)
    {
        return Page(domain, effectiveUrl, bodyResult, status, false);
    }
    return Page(domain, effectiveUrl, bodyResult, status, true);
}

std::size_t PageLoader::write_data(void* ptr, std::size_t size, std::size_t nmemb, std::string* data)
{
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

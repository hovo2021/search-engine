#ifndef WEBSITE_HPP
#define WEBSITE_HPP
#include <string>

class Website
{
private:
    int websiteId;
    std::string domain;
    std::string homepage;
    bool crawled; 

public:
    Website(int websiteId, std::string domain, std::string homepage, bool crawled);
    [[nodiscard]] int getWebsiteId() const;
    [[nodiscard]] const std::string& getDomain() const;
    [[nodiscard]] const std::string& getHomepage() const;
    [[nodiscard]] bool isCrawled() const;
    [[nodiscard]] time_t getLastCrawledTime();
};

#endif

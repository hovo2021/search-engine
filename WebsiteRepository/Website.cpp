#include "Website.hpp"


Website::Website(int websiteId, std::string domain, std::string homepage, bool isCrawled) :
    websiteId(websiteId),
    domain(std::move(domain)),
    homepage(std::move(homepage)),
    crawled(crawled)
{
}

int Website::getWebsiteId() const
{
    return this->websiteId;
}

const std::string& Website::getDomain() const
{
    return this->domain;
}

const std::string& Website::getHomepage() const
{
    return this->homepage;
}

bool Website::isCrawled() const
{
    return this->crawled;
}

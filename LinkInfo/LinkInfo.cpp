#include "LinkInfo.hpp"

LinkInfo::LinkInfo(std::string url, int websiteId, LinkStatus status) :
    url(std::move(url)),
    websiteId(websiteId),
    status(status)
{
}

const std::string& LinkInfo::getUrl() const
{
    return this->url;
}

int LinkInfo::getWebsiteId() const
{
    return this->websiteId;
}

LinkStatus LinkInfo::getStatus() const
{
    return this->status;
}

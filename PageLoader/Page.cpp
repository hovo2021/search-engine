#include "Page.hpp"

Page::Page(std::string& domain, std::string& effectiveUrl, std::string& body, int status, bool exist):
        domain(domain),
        effectiveUrl(effectiveUrl),
        body(body), 
        status(status),
        exist(exist)
        {
        }

Page::~Page() = default;

const std::string& Page::getDomain() const
{
    return this->domain;
}

const std::string Page::getEffectiveUrl() const
{
    return this->effectiveUrl;
}

const std::string& Page::getBody() const
{
    return body;
}

int Page::getStatus() const
{
    return status;
}

bool Page::isExist() const
{
    return this->exist;
}
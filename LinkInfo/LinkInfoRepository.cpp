#include "LinkInfoRepository.hpp"

const std::vector<LinkInfo>& LinkInfoRepository::getAll() const
{
    return this->links;
}

const std::optional<LinkInfo> LinkInfoRepository::getByUrl(const std::string& url) const
{
    for(auto& link : this->links)
    {
        if(link.getUrl() == url)
        {
            return link;
        }
    }

    return {};
}

const std::vector<LinkInfo> LinkInfoRepository::getBy(
    int websiteId, LinkStatus status, int count, sql::Connection* connection) const
{
    std::vector<LinkInfo> linksResult;
    auto prepst = connection->prepareStatement("SELECT * from Links WHERE status=(?) AND websiteId=(?)");
    prepst->setUInt(1, 0);
    prepst->setUInt(2, websiteId);
    auto result = prepst->executeQuery();
    for(int i = 0; i < count; ++i)
    {
        if(!result->next())
        {
            break;
        }
        linksResult.push_back(LinkInfo(result->getString("url"), result->getUInt("websiteId"), static_cast<LinkStatus>(result->getUInt("status"))));
    }
    
    
    return linksResult;
}

void LinkInfoRepository::save(const LinkInfo& link, sql::Connection* connection)
{
    sql::PreparedStatement* prepst;
    prepst = connection->prepareStatement(
        "INSERT INTO Links(url, websiteId, status) VALUES (?, ?, ?) ON DUPLICATE KEY UPDATE url=(?), status=(?)");
    prepst->setString(1, link.getUrl());
    prepst->setInt(2, link.getWebsiteId());
    prepst->setInt(3, static_cast<int>(link.getStatus()));
    prepst->setString(4, link.getUrl());
    prepst->setInt(5, static_cast<int>(link.getStatus()));
    prepst->execute();

    this->links.push_back(link);
}
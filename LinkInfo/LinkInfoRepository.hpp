#ifndef LINKINFOREPOSITORY_HPP
#define LINKINFOREPOSITORY_HPP

#include "LinkInfo.hpp"
#include "mysql.hpp"
#include <vector>
#include <optional>

class LinkInfoRepository
{
private:
    std::vector<LinkInfo> links;

public:
    const std::vector<LinkInfo>& getAll() const;
    const std::optional<LinkInfo> getByUrl(const std::string& url) const;
    const std::vector<LinkInfo> getBy
        (int websiteId, LinkStatus status, int count, sql::Connection* connection) const;

    void save(const LinkInfo& link, sql::Connection* connection);
};

#endif

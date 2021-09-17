#include "WebsiteRepository.hpp"


WebsiteRepository::WebsiteRepository(sql::Connection* connection)
{
    const uint64_t dayBetween = 0; 
    sql::Statement* statement = connection->createStatement();

    sql::PreparedStatement* prepst = connection->prepareStatement(
        "SELECT * FROM Websites WHERE TIMESTAMPDIFF(DAY, lastTime, CURRENT_TIMESTAMP) > (?)");
    prepst->setUInt(1, dayBetween);
    auto result = prepst->executeQuery();

    while(result->next())
    {
        Website website(result->getInt("id"), result->getString("domain"), result->getString("homepage"), false);
        websites.push_back(website);
    }  
}

const std::vector<Website>& WebsiteRepository::getAll() const
{
    return websites;
}

const std::optional<Website> WebsiteRepository::getByDomain(const std::string& domain) const
{
    for(auto website : websites)
    {
        if(website.getDomain() == domain)
        {
            return website;
        }
    }

    return {};
}

void WebsiteRepository::add(const Website& website)
{
    websites.push_back(website);
}

void WebsiteRepository::update(const std::string& domain, const Website& website, sql::Connection* connection)
{
    sql::PreparedStatement* prepst;
    prepst = connection->prepareStatement("UPDATE Websites SET * WHERE domain = (?)");
    prepst->setString(1, domain);

    prepst->execute();
}
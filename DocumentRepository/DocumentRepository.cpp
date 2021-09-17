#include "DocumentRepository.hpp"

void DocumentRepository::add(const Document& document, sql::Connection* connection)
{
    sql::PreparedStatement* prepst;

    prepst = connection->prepareStatement("INSERT INTO Documents(url, title, description, content) VALUES (?, ?, ?, ?) ON DUPLICATE KEY UPDATE url=(?), title=(?), description=(?), content=(?)");
    prepst->setString(1, document.getUrl());
    prepst->setString(2, document.getTitle());
    prepst->setString(3, document.getDescription());
    prepst->setString(4, document.getContent());
    prepst->setString(5, document.getUrl());
    prepst->setString(6, document.getTitle());
    prepst->setString(7, document.getDescription());
    prepst->setString(8, document.getContent());
    prepst->execute();
}

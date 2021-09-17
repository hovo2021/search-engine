#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <string>

class Document
{
private:
    std::string url;
    std::string title;
    std::string description;
    std::string content;

public:
    Document(std::string url, std::string title, std::string description, std::string content);

    [[nodiscard]] const std::string& getUrl() const;
    [[nodiscard]] const std::string& getTitle() const;
    [[nodiscard]] const std::string& getDescription() const;
    [[nodiscard]] const std::string& getContent() const;
};

#endif

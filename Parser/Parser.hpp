#ifndef PARSER_HPP
#define PARSER_HPP

#include <gumbo.h>
#include <vector>
#include <string>
#include <iostream>

class Parser
{
private: // data

    std::vector<std::string> links;
    
    std::string title;
    std::string description;
    std::string content;

    std::string domain;
private: // functions

    void extractLinks(GumboNode* node, const std::string& rootURL);
    void extractTitle(GumboNode* node);
    void extractDescription(GumboNode* node);
    void extractContent(GumboNode* node);
    bool isLinkAbsolute(const std::string& url);
    const std::string getDomain(const std::string& rootURL) const; 

public:
    [[nodiscard]] const std::vector<std::string>& getLinks() const;
    [[nodiscard]] const std::string& getTitle() const;
    [[nodiscard]] const std::string& getDescription() const;
    [[nodiscard]] const std::string& getContent() const;
    
    
    void parse(const std::string& body, const std::string& rootURL, const std::string& urlDomain);
};

#endif

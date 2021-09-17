#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>
class Page
{
private:
    std::string domain;
    std::string effectiveUrl;
    std::string body; // html code
    int status;
    bool exist;
    
public:
    Page(std::string& domain, std::string& effectiveUrl, std::string& body, int status, bool exist);
    ~Page();

    [[nodiscard]] const std::string& getDomain() const;
    [[nodiscard]] const std::string getEffectiveUrl() const;
    [[nodiscard]] const std::string& getBody() const;
    [[nodiscard]] int getStatus() const;
    [[nodiscard]] bool isExist() const;
    
};

#endif

#include "Parser.hpp"

// PLS, DO NOT TOUCH THIS CODE!!!!!!!!!!!!!!!
// It's works on magic

void Parser::parse(const std::string& body, const std::string& rootURL, const std::string& urlDomain)
{
    
    this->domain = urlDomain;
    GumboOutput* output = gumbo_parse(body.c_str());
    if(!output)
    {
        std::cout << "Can't parse this" << std::endl;
        return;
    }

    this->extractLinks(output->root, rootURL);   
    this->extractTitle(output->root);
    this->extractDescription(output->root);
    this->extractContent(output->root);
    
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

void Parser::extractLinks(GumboNode* node, const std::string& rootURL)
{
    if(node->type != GUMBO_NODE_ELEMENT)
    {
        return;
    }

    if(node->v.element.tag == GUMBO_TAG_A)
    {
        GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
        if(href)
        {   
            std::string tmp(href->value);
            if(tmp.find(this->domain) != std::string::npos)
            {
                if(tmp.back() == '/')
                {
                    tmp.pop_back();
                }

                // MySQL unique url required 256 symbols, so just skip this ¯\_(ツ)_/¯
                if(tmp.size() >= 256)
                {
                    return;
                }
                this->links.push_back(tmp); 
            }
            else if (tmp[0] == '/')
            {
                std::string appended(domain); 
                appended.append(tmp);

                if(appended.size() >= 256)
                {
                    return;
                }
                this->links.push_back(appended); 
            }
        }
        return;
    }
    
    GumboVector* children = &node->v.element.children;
    for(std::size_t i = 0; i < children->length; ++i)
    {
        this->extractLinks(static_cast<GumboNode*>(children->data[i]), rootURL);
    }
}

void Parser::extractTitle(GumboNode* node)
{
    if(node->type != GUMBO_NODE_ELEMENT)
    {
        return;
    }

    // find head
    GumboNode* head = NULL;
    GumboVector* nodeChildren = &(node->v.element.children);
    for(auto i = 0; i < nodeChildren->length; ++i)
    {
        GumboNode* child = static_cast<GumboNode*>(nodeChildren->data[i]);

        if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_HEAD)
        {
            head = child;
            break;
        }
    }

    GumboVector* headChildren = &head->v.element.children;
    for(auto i = 0; i < headChildren->length; ++i)
    {
        GumboNode* child = static_cast<GumboNode*>(headChildren->data[i]);

        if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TITLE)
        {
            if(child->v.element.children.length != 1)
            {
                this->title = "<empty title>";
            }
            GumboNode* titleText = static_cast<GumboNode*>(child->v.element.children.data[0]);
            if(titleText->type == GUMBO_NODE_TEXT)
            {
                this->title = titleText->v.text.text;
                return;
            }
        }
    }

    this->title = "<title not found>";
}

void Parser::extractDescription(GumboNode* node)
{
    if(node->type!=GUMBO_NODE_ELEMENT) 
    {
		return;
	}
	
	if(node->v.element.tag!=GUMBO_TAG_META) 
    {
		GumboVector* children = &node->v.element.children;

		for(std::size_t i = 0; i < children->length; ++i) 
        {
			this->extractDescription(static_cast<GumboNode*>(children->data[i]));
		}
	}
	

	GumboAttribute* name = gumbo_get_attribute(&node->v.element.attributes, "name");
	if (name==nullptr || name->value==nullptr || std::string(name->value) != "description") 
    {
		return;
	}

	GumboAttribute* cont = gumbo_get_attribute(&node->v.element.attributes, "content");
	if (cont == nullptr || cont->value == nullptr) 
    {
		return;
	}

	this->description = std::string(cont->value);
}

void Parser::extractContent(GumboNode* node)
{
    if (node->type == GUMBO_NODE_TEXT) 
    {
		this->content.append(std::string(node->v.text.text));
		this->content.append("\n");
	}
    
    if (node->type != GUMBO_NODE_ELEMENT || node->v.element.tag == GUMBO_TAG_STYLE || node->v.element.tag == GUMBO_TAG_SCRIPT) 
    {
		return;
	}


	GumboVector* children = &node->v.element.children;
	for (size_t i = 0; i<children->length; ++i) 
    {
		this->content.append(" ");
		this->extractContent(static_cast<GumboNode*>(children->data[i]));
	}
}

const std::vector<std::string>& Parser::getLinks() const
{
    return this->links;
}

const std::string& Parser::getTitle() const
{
    return this->title;
}

const std::string& Parser::getDescription() const
{
    return this->description;
}
const std::string& Parser::getContent() const
{
    return this->content;
}

bool Parser::isLinkAbsolute(const std::string& url)
{
    if(url.size() < 2)
    {
        return false;
    }

    if(url[0] == '/' && url[1] == '/' || std::string(url, 0, 7) == "http://" || std::string(url, 0, 8) == "https://") 
    {
        return true;
    }

    return false;
}

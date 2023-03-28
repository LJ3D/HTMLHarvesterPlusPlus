#include <iostream>
#include <string>
#include <vector>

namespace HTMLH {

    namespace internal{
        std::vector<std::string> linkTags = {"href","src"};


    }

    std::string getTitle(std::string html){
        size_t pos = html.find("<title>") + 7;
        size_t endpos = html.find("</title>");
        if(pos == std::string::npos){
            return "Title not found";
        }
        if(endpos == std::string::npos){
            return "End of title not found";
        }

        std::string title = html.substr(pos, endpos-pos);
        
        return title;
    }

    std::vector<std::string> getLinks(std::string html){
        std::vector<std::string> urls;
        for(std::string tag : internal::linkTags){
            size_t found = html.find(tag, 0);
            size_t starting = 0;

            while(found != std::string::npos){
                size_t firstQuote = html.find('"', found) + 1;
                size_t secondQuote = html.find('"', firstQuote+1);

                urls.push_back(html.substr(firstQuote, secondQuote-firstQuote));
                starting = secondQuote + 1;
                found = html.find(tag, starting);
            }
        }
        
        return urls;
    }


}
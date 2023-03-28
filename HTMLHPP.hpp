#include <iostream>
#include <string>

namespace HTMLH {

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

}
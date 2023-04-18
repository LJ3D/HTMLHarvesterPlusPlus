#include <string>
#include <vector>


namespace HTMLH {

    namespace internal{

        std::vector<std::string> linkTags = {"href","src"};

    }

    /*
        Find the title of the page by searching for the first <title> tag
    */
    std::string getTitle(const std::string& html){
        size_t pos = html.find("<title>") + 7;
        size_t endpos = html.find("</title>");
        if(pos == std::string::npos){
            return "Title not found"; // Bad err handling
        }
        if(endpos == std::string::npos){
            return "End of title not found"; // Bad err handling
        }
        std::string title = html.substr(pos, endpos-pos);
        return title;
    }

    /*
        Returns a vector of strings by searching the tags in HTMLH::internal::linkTags
        It is recommended to use the HTMLH::cleanlinks on the links returned by this function
    
        This function returns links of all types, from pages to CSS documents
    */
    std::vector<std::string> getLinks(const std::string& html){
        std::vector<std::string> links;
        for(std::string tag : internal::linkTags){ // internal::linkTags contains a list of "tags" that specify links (src, href, etc)
            size_t found = html.find(tag, 0); // Find the first tag
            size_t tagFindStart = 0; // Used to find the next tag (updates to position of end of current link)
            while(found != std::string::npos){
                size_t firstQuote = html.find('"', found) + 1;
                size_t secondQuote = html.find('"', firstQuote+1);
                if(firstQuote == std::string::npos || secondQuote == std::string::npos){
                    break;
                }
                links.push_back(html.substr(firstQuote, secondQuote-firstQuote));

                // Find the next tag
                tagFindStart = secondQuote + 1;
                found = html.find(tag, tagFindStart); // No need to err hande because while loop will break if not found
            }
        }
        return links;
    }

    /*
        Fixes up relative links, etc
    */
    void cleanlinks(std::vector<std::string>& links, const std::string& sourceURL){
        for(auto& url : links){
            // Remove anything after a #
            size_t hash = url.find('#');
            if(hash != std::string::npos){
                url = url.substr(0,hash);
            }

            // Starts with "//" -> add http: (// indicates use the same protocol as the page, but we will ignore that for now and default to http)
            if(url.starts_with("//")){
                url = "http:" + url;
            }

            // Attach url to the front of relative links
            if(!url.starts_with("http")){
                if(!url.starts_with("/")){
                    url = "/" + url;
                }
                url = sourceURL + url;
            }
        }

        // Remove any empty link strings
        for(int i = 0; i< links.size();i++){
            if(links[i] == ""){
                links.erase(links.begin() + i);
                i--;
            }
        }
    }

    /*
        Gets
    */


}
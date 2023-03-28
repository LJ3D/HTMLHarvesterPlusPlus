#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include "../../HTMLHPP.hpp"
#include <vector>


/*
    Function used by libcurl to write data to a string* (set by CURLOPT_WRITEDATA)
*/
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    // userp is the pointer passed to the function setting CURLOPT_WRITEDATA
    // In this case, assume its an std::string*
    ((std::string*)userp)->append((char*)contents, size * nmemb);

    return size * nmemb; // Returns the number of bytes written   
}

#define URL "http://defcom1.net"

int main(void){
    // Init curl
    CURL *curl; // A pointer to the CURL object
    CURLcode res; // A CURLcode object to store the result of curl operations
    curl = curl_easy_init();
    if(!curl){ // Return an error if the CURL object could not be initialized
        return 1;
    }

    // Get the page
    std::string readBuffer;
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    // Write to a file for debugging or whatever
    std::ofstream out("output.html");
    out << readBuffer;
    out.close();

    // Use HTMLHarvester to get information from the page
    std::string title = HTMLH::getTitle(readBuffer);
    std::vector<std::string> links = HTMLH::getLinks(readBuffer);
    HTMLH::cleanlinks(links, URL); // links passed by reference
    
    // Print the information
    std::cout << "Title: " << title << std::endl;
    std::cout << "Links:" << std::endl;
    for(auto i: links){
        std::cout << i << std::endl;
    }

    return 0;
}
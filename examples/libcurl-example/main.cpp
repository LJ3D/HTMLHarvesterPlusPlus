#include <iostream>
#include <string>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    // userp is the pointer passed to the function setting CURLOPT_WRITEDATA
    // In this case, assume its an std::string*
    ((std::string*)userp)->append((char*)contents, size * nmemb);

    return size * nmemb; // Returns the number of bytes written   
}

#define URL "https://www.google.com"

int main(void){
    CURL *curl; // A pointer to the CURL object
    CURLcode res; // A CURLcode object to store the result of curl operations
    
    curl = curl_easy_init();
    if(!curl){ // Return an error if the CURL object could not be initialized
        return 1;
    }

    std::string readBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    
    // ... HTMLHarvester code goes here ...
    std::cout << readBuffer << std::endl;
    
    return 0;
}
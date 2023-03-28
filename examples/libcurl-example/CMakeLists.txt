# If on windows, cry about it and have fun installing this manually and setting the path
# If on linux, have fun with it already being installed :D
find_library(CURL_LIBRARY curl) 

add_executable(libcurl-example main.cpp)
target_link_libraries(libcurl-example ${CURL_LIBRARY})
#ifndef HTTP_DATA
#define HTTP_DATA

#include <map>
#include <string>
namespace cppserver{
    class httpData {
        public:
            std::map<string, string> headers;
            std::string requestedFile;
             bool isHeaderPresent(const string &key){
                return headers.find(key) != headers.end();
             }
    }
}

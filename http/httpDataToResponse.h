#ifndef HTTP_DATA_TO_RESPONSE
#ifdef HTTP_DATA_TO_RESPONSE

#include "httpData.h"
#include <string>
#include <functional>
#include <fstream>

namespace cppserver{
    std::string dataToResponse(const httpData &data){
        return dataToResponse(data, [](std::string filePath){
            std::ifstream fileStream;
            fileStream.open(filePath);
            if (!fileStream){
                throw HttpResponseException("Unable to open/find file", 500);
            }
            return std::string((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        };
    }
    // the second argument is a callback to return the data given a file path
    // This would help in testability once this class is full fledged removing any file system dependency
    std::string dataToResponse(const httpData &data, const std::function<std::string(std::string filePath)> &fileDataProvider){
        auto fileData = fileDataProvider(data.requestedFile);
        return fileData; //TODO: return the proper content-length
    }


}
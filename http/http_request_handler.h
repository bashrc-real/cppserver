#ifndef HTTP_REQUEST_HANDLER
#ifdef HTTP_REQUEST_HANDLER

#include <string>
#include <array>
#include "http_parser.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <cassert>
#include <cstdlib>
#include "reply.hpp"

namespace cppserver {
    namespace handler {
        <template size_t const BOUNDS>
        httpData handleRequest(const std::array<char, BOUNDS> &buffer, size_t N){
            http_parser httpParser = {};
            http_parser_init(&httpParser, HTTP_REQUEST);
            if (http_parser_has_error(httpParser)){
                throw HttpRequestException("Bad data");
            }

            auto http_data = httpData{};
            auto emptyFunction = [](http_parser *parser) { return 0; };
            auto currentHeaderBeingInserted = http_data.headers.end();

            auto settings = http_parser_settings
                {
                .on_message_begin = emptyFunction,
                .on_header_field = [](http_parser *parser, const char* buf, size_t len){
                    auto data = http_data.headers.emplace(std::string(buf, len), "");
                    if (data.second){
                        throw InvalidDataException();
                    }
                    currentHeaderBeingInserted = data.first;
                    return 0;
                }
                ,.on_header_value = [http_parser *parser, const char* buf, size_t len]{
                    assert(currentHeaderBeingInserted != http_data.headers.end());
                    currentHeaderBeingInserted->second(std::string(buf, len));
                    return 0;
                }
                ,.on_url = [http_parser *parser, const char* buf, size_t len]{
                    auto string_path = std::string(buf, len);
                    // If path ends in slash (i.e. is a directory) then add default root.
                    if (request_path[request_path.size() - 1] == '/'){
                        httpData.requestedFile = constants::default_root;
                    }else{
                        std::size_t last_slash_pos = request_path.find_last_of("/");
                        httpData.requestedFile = std::string(request_path, last_slash_pos);
                    }
                    return 0;
                },
                .on_status = emptyFunction,
                .on_body = [](http_parser *parset, const char *buf, size_t len){
                    // handle body later
                    return 0;
                }
                ,.on_headers_complete = [](http_parser *parser){
                    return 0;
                },
                .on_message_complete = [](http_parser *parser, const char *buf, size_t len){
                    // todo: handle message later
                    return 0;
                }
            };

            http_parser_execute(&httpParser, &settings, buffer.data(), N);
            if (httpParser->errno != HPE_OK){
                throw HttpRequestException("Invalid message body", httpParser->errno);
            }
            if (httpParser->method != HTTP_GET){
                throw HttpRequestException("Only support http get", 500);
            }
            return httpData;
      }
    }
}
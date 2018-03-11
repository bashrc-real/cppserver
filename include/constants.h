#ifndef CONSTANTS
#define CONSTANTS

namespace cppserver {
    namespace constants{
        const size_t buffer_length = 1024 * 4; // todo- benchmark
        const string default_content_length_header = "Content-Length";
        const string default_content_type_header = "Content-Type";
        const string default_content_type = "text/html";
        const string default_root = "index.html";
    }
}
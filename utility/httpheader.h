#ifndef HTTPHEADER

#define HTTPHEADER
#include <string>
namespace cppserver {
    namespace utility {
        struct header {
            std::string name;
            std::string value;
        };
    }
}
#endif
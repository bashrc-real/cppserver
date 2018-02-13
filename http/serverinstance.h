#ifndef SERVERINSTANCE
#define SERVERINSTANCE

#include <string>
#include <functional>
#include <future>   
#include <queue>

namespace cppserver{
    class serverInstance{
public:
        serverInstance();
        void open();
        void close();
        std::future<void> handle_message(const std::wstring &message);
private:
        std::queue<std::wstring> m_messageQueue;
        bool isOpen = false;
    };
}
#endif
#ifndef SERVERINSTANCE
#define SERVERINSTANCE

#include <string>
#include <functional>
#include <future>   
#include <queue>
#include <boost/asio.hpp>
namespace cppserver{
    class serverInstance{
public:
        serverInstance(int port);
        void open();
        void close();
        void run();
        std::future<void> handle_message(const std::wstring &message);
private:
        std::queue<std::wstring> m_messageQueue;
        boost::asio::io_service m_ioservice;
        boost::asio::ip::tcp::acceptor m_acceptor;
        boost::asio::ip::tcp::endpoint m_endpoint;

        bool isOpen = false;
    };
}
#endif
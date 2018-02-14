#include "serverinstance.h"
#include <cassert>
#include <boost/asio.hpp>

namespace cppserver{
    serverInstance::serverInstance(){
    }

    void serverInstance::open(int port){
        assert(port > 0 && port <= ((1 << 15) - 1));
        boost::asio::io_service ioservice;
        boost::asio::ip::tcp::acceptor Acceptor(ioservice);
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
        Acceptor.open(endpoint.protocol());
        Acceptor.bind(endpoint);
        Acceptor.listen();
        isOpen = true;
    }

    void serverInstance::close(){
        isOpen = false;
    }

    std::future<void> serverInstance::handle_message(const std::wstring &message){
        m_messageQueue.emplace(message);
    }
   


}
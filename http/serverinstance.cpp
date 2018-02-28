#include "serverinstance.h"
#include <cassert>

namespace cppserver{
    serverInstance::serverInstance(int port) : m_acceptor(m_ioservice),
                                               m_endpoint(boost::asio::ip::tcp::v4(), port){}

    void serverInstance::open(){
        if (isOpen) return;
        m_acceptor.open(m_endpoint.protocol());
        m_acceptor.bind(m_endpoint);
        m_acceptor.listen();
        
        isOpen = true;
    }

    void serverInstance::close(){
        isOpen = false;
    }

    std::future<void> serverInstance::handle_message(const std::wstring &message){
        m_messageQueue.emplace(message);
    }
   


}
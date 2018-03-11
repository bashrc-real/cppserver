#include "serverinstance.h"
#include <cassert>

namespace cppserver{
    serverInstance::serverInstance(int port) : m_acceptor(m_ioservice),
                                               m_endpoint(boost::asio::ip::tcp::v4(), port){}

    void serverInstance::open(){
        if (isOpen) return;
        m_acceptor.open(m_endpoint.protocol());
        m_acceptor.bind(m_endpoint);
        m_socket(m_ioservice);
        m_acceptor.listen();
        m_acceptor.async_accept()
        isOpen = true;
    }

    void serverInstance::close(){
        isOpen = false;
    }

    void connection::write(const httpData &httpDataObject}
    {
      auto self(shared_from_this());
      boost::asio::async_write(m_socket, replyObject.data(),
      [this, self](boost::system::error_code ec, std::size_t)
      {
        if (!ec)
        {
          // Initiate graceful connection closure.
          boost::system::error_code ignored_ec;
          m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
            ignored_ec);
        }

        if (ec != boost::asio::error::operation_aborted)
        {
           // TODO: handle aborted
        }
      });
  }

    void serverInstance::run(){
        m_socket.async_read_some(boost::asio::buffer(m_buffer),
      [this, self](boost::system::error_code ec, std::size_t bytesTransferred)
      {
        if (!ec)
        {
            write(handler::handleRequest(m_buffer).data());
        }
        else
        {
          run();
        }
        else if (ec != boost::asio::error::operation_aborted)
        {
            // TODO: handle aborted
        }
      });
    }
}
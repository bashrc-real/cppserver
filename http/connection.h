#ifndef CONNECTION
#define CONNECTION

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include <function>

namespace cppserver {

class connection {
public:
  // deleting the copy semantics because this class owns the reference to the socket
  // Multiple instances sharing the same socket would be problematic.
  connection(const connection&) = delete;
  connection& operator=(const connection&) = delete;
  
  connection(connection &&lhs){
    m_buffer = std::move(lhs.m_buffer);
    m_socket = std::move(lhs.m_socket);
  }

  connection(boost::asio::ip::tcp::socket socket, uint64_t id, 
             const std::function<bool(uint64_t)> &onClosed) : m_socket(std::move(socket)), m_connectionId(id), m_callback(onClosed){}

  // start the connection
  void start();

  // stop the connection.
  // Precondition: connection::start must have been called.
  void stop();

private:
  void do_read();
  void do_write();

  // The connection id is a unique identifier. The connection needs to relay back its state to the
  // manager object. One alternative is to use a smart pointer (like shared_ptr) and use the ordering
  // semantics provided by it inherently. But that has contention overhead because of the locking 
  // and additional memory overhead because of enable_shared_from_this. 
  // Keeping an integer identifier may not be clean but is a compromise for performance
  uint64_t m_connectionId; 

  boost::asio::ip::tcp::socket m_socket;

  /// Buffer for incoming data.
  std::array<char, constants::buffer_length> m_buffer;

  std::function<bool(uint64_t)> m_callback;
};

} // namespace server

#endif


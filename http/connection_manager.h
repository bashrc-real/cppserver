#ifndef CONNECTION_MANAGER
#define CONNECTION_MANAGER

#include <set>
#include "connection.hpp"

namespace cppserver {

typedef boost::asio::ip::tcp::socket connection_socket;

class connection_manager {
public:

  // add the socket to the pool and create a new connection from it
  void create_add(connection_socket c);

  /// Stop all connections.
  void stop_all();

private:
  /// Pool of managed connections
  std::map<uint64_t, std::unique_ptr<connection>> m_connections;
};
} // namespace cppserver
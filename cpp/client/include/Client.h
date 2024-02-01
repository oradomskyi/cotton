#ifndef COTTON_CLIENT_H
#define COTTON_CLIENT_H

#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <functional>
#include <iostream>
#include <string>

using boost::asio::steady_timer;
using boost::asio::ip::tcp;
using std::placeholders::_1;
using std::placeholders::_2;

class Client
{
public:
    Client(boost::asio::io_context& io_context);
    
    void start(tcp::resolver::results_type endpoints);
    void stop();
    void operator()(tcp::resolver::results_type endpoints);
    
private:

    void start_connect(tcp::resolver::results_type::iterator endpoint_iter);
    void handle_connect(const boost::system::error_code& error,
      tcp::resolver::results_type::iterator endpoint_iter);
    
    void start_read();
    void handle_read(const boost::system::error_code& error, std::size_t n);
    
    void start_write();
    void handle_write(const boost::system::error_code& error);

    void check_deadline();
    
private:
  bool stopped_ = false;
  int DEADLINE_CONNECT_SEC = 60;
  int DEADLINE_WRITE_SEC = 10;
  int DEADLINE_READ_SEC = 30;
  
  tcp::resolver::results_type endpoints_;
  tcp::socket socket_;
  std::string input_buffer_;
  std::string output_buffer_;
  steady_timer deadline_;
  steady_timer heartbeat_timer_;

};

#endif
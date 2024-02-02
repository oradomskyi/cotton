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

#include "ClientInterface.h"



using boost::asio::steady_timer;
using boost::asio::ip::tcp;
using std::placeholders::_1;
using std::placeholders::_2;

namespace cotton {
    
class Client : public ClientInterface
{
public:
    Client(boost::asio::io_context& io_context, tcp::resolver::results_type& endpoints);

    // kind-a too much
    //Client(Client&& other)
  //: endpoints_(std::move(other.endpoints_))
  //, socket_(std::move(other.socket_))
  //, deadline_(std::move(other.deadline_))
  //, heartbeat_timer_(std::move(other.heartbeat_timer_))
  //, input_buffer_(std::move(other.input_buffer_))
  //, output_buffer_(std::move(other.output_buffer_))
  //{std::cout << "Client move" << std::endl;};

    virtual void start();
    virtual void stop();
    virtual void operator()();
    
protected:

    virtual void start_connect(tcp::resolver::results_type::iterator endpoint_iter);
    virtual void handle_connect(const boost::system::error_code& error,
      tcp::resolver::results_type::iterator endpoint_iter);
    
    virtual void start_read();
    virtual void handle_read(const boost::system::error_code& error, std::size_t n);
    
    virtual void start_write();
    virtual void handle_write(const boost::system::error_code& error);

    void check_deadline();
    
protected:
  bool stopped_ = false;
  int DEADLINE_CONNECT_SEC = 60;
  int DEADLINE_WRITE_SEC = 10;
  int DEADLINE_READ_SEC = 30;
  
  tcp::resolver::results_type endpoints_;
  tcp::socket socket_;
  steady_timer deadline_;
  steady_timer heartbeat_timer_;
  std::string input_buffer_;
  std::string output_buffer_="Hello from default async client!";

};

} // cotton

#endif
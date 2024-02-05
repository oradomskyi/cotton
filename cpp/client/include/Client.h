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
#include <time.h>

#include "ClientInterface.h"

namespace cotton {

using std::size_t;
using std::string;
using std::placeholders::_1;
using std::placeholders::_2;

using boost::asio::steady_timer;
using boost::asio::ip::tcp;
using boost::asio::io_context;
using boost::system::error_code;


class Client //: public ClientInterface
{
public:
    Client(io_context& io_context, tcp::resolver::results_type endpoints);
          
    virtual void start();
    virtual void stop();
    virtual void operator()();
    
protected:

    virtual void start_connect(tcp::resolver::results_type::iterator endpoint_iter);
    virtual void handle_connect(const error_code& error,
      tcp::resolver::results_type::iterator endpoint_iter);
    
    virtual void start_read();
    virtual void handle_read(const error_code& error, std::size_t n);
    
    virtual void start_write();
    virtual void handle_write(const error_code& error);

    void check_deadline();
    
protected:
  bool stopped_ = false;
  int DEADLINE_CONNECT_MS_ = 60000; // 60 seconds
  int DEADLINE_WRITE_MS_ = 10000; // 10 sec
  int DEADLINE_READ_MS_ = 30000; // 30 sec 
  
  tcp::resolver::results_type endpoints_;
  tcp::socket socket_;
  steady_timer deadline_;
  steady_timer heartbeat_timer_;
  string input_buffer_;
  string output_buffer_="Hello from default async client!";

};

} // cotton

#endif
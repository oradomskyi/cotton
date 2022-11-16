#ifndef NETWORK_BOOSTASIO_H
#define NETWORK_BOOSTASIO_H

#include <iostream> // remove when not needed

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include "../Network.h"

using std::cout; // remove when not needed, this is for debug only
using std::endl; // remove when not needed, this is for debug only

using std::string;
using std::to_string;

using boost::asio::steady_timer;
using boost::asio::ip::tcp;
using std::placeholders::_1;
using std::placeholders::_2;

namespace boostasio
{
    void run(const boost::system::error_code& e,boost::asio::steady_timer* t, int* count);
}

//https://www.boost.org/doc/libs/1_74_0/doc/html/boost_asio/example/cpp11/timeouts/async_tcp_client.cpp
class BoostAsio : public Network
{
private:
    static const network::Type type = network::Type::BOOST_ASIO;
    string address;
	uint16_t port;
    boost::asio::io_context io;
    tcp::resolver* tcp_resolver;
    tcp::resolver::results_type endpoints;
    tcp::socket* socket;

    string output_buffer;

    void start_connect(tcp::resolver::results_type::iterator endpoint_iter);
    void check_deadline();
    void handle_connect(const boost::system::error_code& error,
      tcp::resolver::results_type::iterator endpoint_iter);

    void handle_write(boost::asio::io_context *_io, network::State *_state);
public:
	BoostAsio();
    BoostAsio(const string& address, const uint16_t& port);
    ~BoostAsio();

    network::Result send(const string& buffer);
    network::Result receive(string& buffer);
    
    network::Type getType() { return this->type; }; 
};
#endif

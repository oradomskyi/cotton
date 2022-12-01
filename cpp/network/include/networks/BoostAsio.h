#ifndef NETWORK_BOOSTASIO_H
#define NETWORK_BOOSTASIO_H

#include <iostream> // remove when not needed

#include <mutex>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include "../Network.h"

using std::mutex;
using std::lock_guard;

using std::cout; // remove when not needed, this is for debug only
using std::endl; // remove when not needed, this is for debug only

using std::string;
using std::to_string;

using boost::asio::steady_timer;
using boost::asio::ip::tcp;
using std::placeholders::_1;


// https://www.boost.org/doc/libs/1_74_0/doc/html/boost_asio/example/cpp11/timeouts/async_tcp_client.cpp
class BoostAsio : public Network
{
private:
    static const network::Type type = network::Type::BOOST_ASIO;

    boost::asio::io_context io;
    tcp::resolver tcp_resolver;
    tcp::resolver::results_type endpoints;
    tcp::socket socket;

	// https://stackoverflow.com/questions/40561097/read-until-a-string-delimiter-in-boostasiostreambuf
	static BoostAsio* _instance;
	static mutex _mutex;

private:

	BoostAsio();
    BoostAsio(const string& address, const uint16_t& port);
    ~BoostAsio();

    void start_connect(tcp::resolver::results_type::iterator endpoint_iter);
    void handle_connect(const boost::system::error_code& error,
      tcp::resolver::results_type::iterator endpoint_iter);

    void handle_write(const boost::system::error_code& error);
    void handle_read(const boost::system::error_code& error);

	BoostAsio(BoostAsio& other) = delete;
	void operator = (const BoostAsio&) = delete; 

public:
	static BoostAsio* getInstance(const string& address, const uint16_t& port);

    network::Result send(const string& buffer);
    network::Result receive(string* buffer);
    
    network::Type getType() { return this->type; }; 
};
#endif

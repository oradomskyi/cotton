#ifndef NETWORK_BOOSTASIO_H
#define NETWORK_BOOSTASIO_H

#include <iostream> // remove when not needed

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include "../Network.h"

using std::cout; // remove when not needed, this is for debug only
using std::endl; // remove when not needed, this is for debug only

using std::string;

namespace boostasio
{
    void run(const boost::system::error_code& e,boost::asio::steady_timer* t, int* count);
}

class BoostAsio : public Network
{
private:
    static const network::Type type = network::Type::BOOST_ASIO;
    string address;
	uint16_t port;
    boost::asio::steady_timer* timer;
    boost::asio::io_context io;
    
public:
	BoostAsio();
    BoostAsio(const string& address, const uint16_t& port);
    ~BoostAsio();

    network::Result Create();
    network::Result Resolve();
    network::Result Connect();
    network::Result Write(const string& data);
    network::Result Disconnect();
    network::Result Shutdown();

    network::Type getType() { return this->type; }; 

	void setAddress(const string& address) { this->address = address; };   // not sure this is a good design decision to have a copy of host and port
	void setPort(const uint16_t& port) { this->port = port; }; // not sure this is a good design decision to have a copy of host and port
};
#endif

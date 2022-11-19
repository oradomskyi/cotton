#ifndef NETWORK_H
#define NETWORK_H

// https://forums.opensuse.org/showthread.php/450418-pthread_exit-c-and-FATAL-exception-not-rethrown
#include <cxxabi.h>

#include <string>
#include "NetworkInterface.h"

using std::string;

class Network : public NetworkInterface
{
protected:
	network::State state;
	string address;
	uint16_t port;

protected:
	void setState(const network::State& new_state);

public:
	Network();
    Network(const string& _address, const uint16_t& _port);
	virtual ~Network();

	network::State getState();
};
#endif

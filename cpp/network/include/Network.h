#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include "NetworkInterface.h"

using std::string;

class Network : public NetworkInterface
{
protected:
	network::State state;
	void setState(network::State new_state) { this->state = new_state; };

public:
	Network();
	virtual ~Network();

	network::State getState() { return this->state; };
};
#endif

#ifndef NETWORK_H
#define NETWORK_H

#include "NetworkInterface.h"

namespace network
{

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

} // namespace Network

#endif

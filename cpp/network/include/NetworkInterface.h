#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include "constants.h"
#include "NetworkHandle.h"

namespace network
{

class NetworkInterface
{
protected:
	NetworkState state;

	void setState(NetworkState new_state) { this->state = new_state; };
	
public:
	virtual void connect() = 0;
	virtual void disconnect() = 0;
	virtual NetworkHandle* getHandle() = 0;
	
	NetworkState getState() { return this->state; };
};

} // namespace Network

#endif

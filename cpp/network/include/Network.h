#ifndef NETWORK_H
#define NETWORK_H

#include "NetworkInterface.h"
#include "NetworkHandle.h"

namespace network
{

class Network : public NetworkInterface
{
private:
	NetworkHandle* handle; // I keep pointer, so it could be either local or global
	
public:
	Network();
	virtual ~Network();
	
	void connect();
	void disconnect();
	NetworkHandle* getHandle();
};

} // namespace Network

#endif

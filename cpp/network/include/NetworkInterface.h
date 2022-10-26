#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include "constants.h"

namespace network
{

class NetworkInterface
{
public:
	virtual void connect() = 0;
	virtual void write() = 0;
	virtual void disconnect() = 0;
    virtual network::Type getType() = 0;
    virtual network::State getState() = 0;
};

} // namespace Network

#endif

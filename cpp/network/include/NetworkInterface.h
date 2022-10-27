#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include "constants.h"

class NetworkInterface
{
public:
	virtual void Connect() = 0;
	virtual void Write() = 0;
	virtual void Disconnect() = 0;
    virtual network::Type getType() = 0;
    virtual network::State getState() = 0;
};
#endif

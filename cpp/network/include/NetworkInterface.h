#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <string>
#include "constants.h"

using std::string;

class NetworkInterface
{
public:
    virtual network::Result Create() = 0;
    virtual network::Result Resolve() = 0;
	virtual network::Result Connect() = 0;
	virtual network::Result Write(const string& data) = 0;
	virtual network::Result Disconnect() = 0;
    virtual network::Result Shutdown() = 0;
    virtual network::Type getType() = 0;
    virtual network::State getState() = 0;
};
#endif

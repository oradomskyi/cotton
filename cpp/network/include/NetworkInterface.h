#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <string>
#include "constants.h"

using std::string;

class NetworkInterface
{
public:
	virtual void Connect() = 0;
	virtual void Write(const string& data) = 0;
	virtual void Disconnect() = 0;
    virtual network::Type getType() = 0;
    virtual network::State getState() = 0;
};
#endif

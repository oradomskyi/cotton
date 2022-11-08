#ifndef PROXY_H
#define PROXY_H

#include "IPPort.h"

class Proxy : public IPPort
{
public:
	Proxy(const string& address, const uint16_t& port)
		:IPPort(address, port)
	{};
	
};

#endif

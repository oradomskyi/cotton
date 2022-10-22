#ifndef PROXY_H
#define PROXY_H

#include "IPPort.h"

class Proxy : public IPPort
{
public:
	Proxy(string address, uint16_t port)
		:IPPort(address, port)
	{};
	
	Proxy(const Proxy& other)
		:IPPort(other.address, other.port)
	{};
};

#endif

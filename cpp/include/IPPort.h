#ifndef IPPORT_H
#define IPPORT_H

#include <string>
using std::string;

class IPPort
{
protected:
	string address;
	uint16_t port;
public:
	IPPort(string address, uint16_t port)
		:address(address)
		,port(port)
	{};
	
	string getAddress() { return this->address; };
	
	uint16_t getPort() { return this->port; };
};

#endif

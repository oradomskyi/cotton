#ifndef METHOD_GET_H
#define METHOD_GET_H

#include "../TCPFlood.h"

class MethodGET : public TCPFlood
{
public:
	MethodGET(std::string address, uint16_t port);
	
	void start();
	void stop();
};

#endif

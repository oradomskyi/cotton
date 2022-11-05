#ifndef METHOD_GET_H
#define METHOD_GET_H

#include <iostream>

#include "../TCPFlood.h"


using std::cout;
using std::endl;

class GET : public TCPFlood
{
private:
	static const flood::RequestType type = flood::RequestType::GET;
	string requestRawPathQS;
	string requestBody;

	// it is up to a particular method to init proper instance of a network
	// TCP or UDP in case of glibc Sockets
	void initNetwork() override;

public:
	GET(std::string address, uint16_t port);
	
	void enable();
	void run();
	void disable();
    flood::RequestType getType() { return this->type; };
};

#endif

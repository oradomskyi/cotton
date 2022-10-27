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
public:
	GET(std::string address, uint16_t port);
	
	void start();
	void stop();
    flood::RequestType getType() { return this->type; };
};

#endif

#ifndef METHOD_GET_H
#define METHOD_GET_H

#include "../TCPFlood.h"
#include "../constants.h"

class MethodGET : public TCPFlood
{
private:
	static const RequestType requestType = RequestType::GET;
	string requestRawPathQS;
	string requestBody;
public:
	MethodGET(std::string address, uint16_t port);
	
	void start();
	void stop();
};

#endif

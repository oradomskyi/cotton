#ifndef TCPFLOOD_H
#define TCPFLOOD_H

#include "Flood.h"

class TCPFlood : public Flood
{
protected:
	string header;
	string request;
	
	void createHeader();
	void createRequest();
public:
	TCPFlood(string address, uint16_t port);
	
	string& getHeader();
	string& getRequest();
};

#endif

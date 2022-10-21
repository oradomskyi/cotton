#ifndef TCPFLOOD_H
#define TCPFLOOD_H

#include <time.h>
#include "Flood.h"
#include "constants.h"
#include "useragents.h"
#include "ProxyManager.h"

using std::to_string;

class TCPFlood : public Flood
{
protected:
	string request;
	string header;

	string defaultHeader;
	
	void setHeader(const string& headers);
	
	void createRequest(RequestType reqestType, const string& qsPathRaw, const string& body);
	
public:
	TCPFlood(string address, uint16_t port);
	
	const string& getHeader() const;
	const string& getRequest() const;
	const string& getDefaultHeader() const;
};

#endif

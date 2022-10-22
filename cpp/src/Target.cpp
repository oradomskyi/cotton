#include "../include/Target.h"

Target::Target(string address, uint16_t port)
	: IPPort(address, port) 
{}

void Target::updateProxy() { /* UNFINUSHED */ }

void Target::updateProxy(const Proxy& proxy)
{ 
	this->proxyPtr = &proxy;
}

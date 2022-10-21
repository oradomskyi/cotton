#include "../include/Target.h"

Target::Target(string address, uint16_t port)
	: IPPort(address, port) 
{
	// UNFINISHED
	this->proxy = new Proxy(string("1.1.1.1"), 111);
}

Proxy* Target::getProxy() { return this->proxy; } 

void Target::updateProxy() { /* UNFINUSHED */ }

void Target::UpdateProxy(string url)
{ 
/* UNFINUSHED */
	url = "2";
}

#include "../include/Flood.h"

Flood::Flood(string address, uint16_t port)
	:target(address, port)
{
	this->initNetwork();
}

Flood::~Flood()
{
	this->networkPtr->~Network();
	delete this->networkPtr;
}

Target* Flood::getTarget()
{ 
	return &this->target;
}

void Flood::initNetwork()
{
	this->networkPtr = new Network();
}

Network* Flood::getNetworkPtr()
{
	return this->networkPtr;
}

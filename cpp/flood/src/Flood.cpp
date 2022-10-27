#include "../include/Flood.h"

Flood::Flood(string address, uint16_t port)
	: target(address, port)
    , networkPtr(nullptr)
    , state(flood::State::ERROR)
{}

Flood::~Flood()
{
	delete this->networkPtr;
}

Target* Flood::getTarget()
{ 
	return &this->target;
}

Network* Flood::getNetworkPtr()
{
	return this->networkPtr;
}



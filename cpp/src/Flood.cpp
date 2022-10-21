#include "../include/Flood.h"

Flood::Flood(string address, uint16_t port)
	:target(address, port)
{}

Target* Flood::getTarget()
{ 
	return &this->target;
}

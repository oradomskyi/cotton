#include "../../include/methods/MethodGET.h"

MethodGET::MethodGET(string address, uint16_t port)
	:TCPFlood(address, port)
{
	this->setState(FloodState::READY);
}
	
void MethodGET::start()
{
	this->setState(FloodState::RUNNING);
}
void MethodGET::stop()
{
	this->setState(FloodState::HALT);
}

#include "../../include/methods/MethodGET.h"

MethodGET::MethodGET(string address, uint16_t port)
	:TCPFlood(address, port)
	, requestRawPathQS("/") // TODO: find out parsing similar to Python's YARL
	, requestBody("")
{	
	this->setHeader(this->getDefaultHeader());
	
	this->createRequest(this->requestType, requestRawPathQS, requestBody);
	
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

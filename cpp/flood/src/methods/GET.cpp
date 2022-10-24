#include "../../include/methods/GET.h"

GET::GET(string address, uint16_t port)
	:TCPFlood(address, port)
	, requestRawPathQS("/") // TODO: find out parsing similar to Python's YARL
	, requestBody("")
{	
	this->setHeader(this->getDefaultHeader());
	
	this->createRequest(this->requestType, requestRawPathQS, requestBody);
	
	this->getTarget()->updateProxy(ProxyManager::getInstance()->getRandomProxy());
	
	this->setState(flood::State::READY);
}

void GET::start()
{
	this->setState(flood::State::RUNNING);
}

void GET::stop()
{
	this->setState(flood::State::HALT);
}

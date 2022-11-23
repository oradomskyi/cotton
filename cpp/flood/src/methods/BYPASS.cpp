#include "../../include/methods/BYPASS.h"

BYPASS::BYPASS(const string& address, const uint16_t& port)
	: TCPFlood(address, port)
	, requestRawPathQS("/") // TODO: find out parsing similar to Python's YARL
	, requestBody("")
{	
	this->setHeader(this->getDefaultHeader());
	
	this->createRequest(this->type, requestRawPathQS, requestBody);
	
	this->getTarget()->updateProxy(ProxyManager::getInstance()->getRandomProxy());
	
	this->initNetwork();

	if(network::State::CREATED <= this->getNetworkPtr()->getState())
	{
        this->setState(flood::State::READY);
        return;
    }
    
    this->setState(flood::State::ERROR);
}

void BYPASS::enable()
{
	this->setState(flood::State::READY);
}

void BYPASS::run()
{
    //printf("GET::run()");
    //cout<<this->getState() << ' ' << this->getNetworkPtr()->getState() << endl;
	if(flood::State::READY != this->getState())
	{
		return;
	}
    {
	this->state = flood::State::RUNNING;
	// it is better to keep connection alive to avoid overhead	
    // https://stackoverflow.com/questions/20599570/is-it-better-to-keep-a-socket-open-for-frequent-requests-or-to-close-the-socket
    
    // TODO:
    // Implement proper logic of GET attack method here
    this->getNetworkPtr()->send("GET /index.html");//this->header);

    // testing read response    
    string buf;
    this->getNetworkPtr()->receive(&buf);
        if(!buf.empty())    
        {
            cout << buf<<endl;
    
            this->state = flood::State::READY;
        }
    }
}

void BYPASS::disable()
{
	this->setState(flood::State::HALT);
}

void BYPASS::initNetwork()
{
    //this->networkPtr = new SocketGLIBC(this->getTarget()->getAddress(), this->getTarget()->getPort());
	this->networkPtr = new BoostAsio(this->getTarget()->getAddress(), this->getTarget()->getPort());
}

void BYPASS::operator()()
{
    if(network::State::CREATED <= this->getNetworkPtr()->getState())
        this->run();
}

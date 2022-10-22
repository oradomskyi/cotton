#include "../include/Network.h"

namespace network
{

Network::Network()
	: handle(nullptr)
{
	setState(NetworkState::READY);
}
Network::~Network()
{}

void Network::connect()
{
	setState(NetworkState::CONNECTED);
}

void Network::disconnect()
{
	setState(NetworkState::READY);
}

NetworkHandle* Network::getHandle()
{
	return this->handle;
}

}

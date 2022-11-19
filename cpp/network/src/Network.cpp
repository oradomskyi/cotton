#include "../include/Network.h"

Network::Network()
        : state(network::State::ERROR)
        , address("")
        , port(0)    
{}

Network::Network(const string& _address, const uint16_t& _port)
        : state(network::State::ERROR)
        , address(_address)
        , port(_port)    
{}

Network::~Network()
{}

void Network::setState(const network::State& new_state)
{
    this->state = new_state;
}

network::State Network::getState()
{
    return this->state;
}

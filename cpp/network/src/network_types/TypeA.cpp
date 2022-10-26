#include "../../include/network_types/TypeA.h"

network::TypeA::TypeA()
    : network::Network()
{

    int sock = socket(PF_INET, SOCK_DGRAM, 0);

    cout << "socket is " << sock << endl;
}

network::TypeA::~TypeA()
{}

void network::TypeA::connect()
{

    this->setState(network::State::ERROR);
}

void network::TypeA::write()
{
    
}

void network::TypeA::disconnect()
{
    this->setState(network::State::ERROR); 
}

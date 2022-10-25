#include "../../include/network_types/TypeA.h"

network::TypeA::TypeA()
    : network::Network()
{}

network::TypeA::~TypeA()
{}

void network::TypeA::connect() { this->setState(network::State::ERROR); };
void network::TypeA::disconnect() { this->setState(network::State::ERROR); };

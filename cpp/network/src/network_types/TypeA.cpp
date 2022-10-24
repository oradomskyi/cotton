#include "../../include/network_types/TypeA.h"

TypeA::TypeA()
    : Network()
{
    
}

TypeA::connect() { setState(network::State::ERROR); };
TypeA::disconnect() { setState(network::State::ERROR); };

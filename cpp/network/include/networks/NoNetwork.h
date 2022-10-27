#ifndef NONETWORK_H
#define NONETWORK_H

#include "../Network.h"

class NoNetwork : public Network
{
private:
    static const network::Type type = network::Type::NO_NETWORK;
public:
    NoNetwork()
        : Network()
    {};

    ~NoNetwork()
    {};

    void Connect() { setState(network::State::ERROR); };
    void Write() { setState(network::State::ERROR); };
    void Disconnect() { setState(network::State::ERROR); };    
    network::Type getType() { return this->type; }; 
};
#endif

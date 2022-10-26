#ifndef NONETWORK_H
#define NONETWORK_H

#include "../Network.h"

namespace network
{

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

    void connect() { setState(network::State::ERROR); };
    void write() { setState(network::State::ERROR); };
    void disconnect() { setState(network::State::ERROR); };    
    network::Type getType() { return this->type; }; 
};

}
#endif

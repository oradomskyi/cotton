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
    void Write(const string& data) { data[0]; setState(network::State::ERROR); }; // when in production remove data[0] that sits there only to make compiler not to complain because of unused variable
    void Disconnect() { setState(network::State::ERROR); };    
    network::Type getType() { return this->type; }; 
};
#endif

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

    network::Result Create() { setState(network::State::ERROR); return network::Result::RESULT_ERROR; };    
    network::Result Resolve() { setState(network::State::ERROR); return network::Result::RESULT_ERROR; };    
    network::Result Connect() { setState(network::State::ERROR); return network::Result::RESULT_ERROR; };
    network::Result Write(const string& data) { data[0]; setState(network::State::ERROR); return network::Result::RESULT_ERROR; }; // when in production remove data[0] that sits there only to make compiler not to complain because of unused variable
    network::Result Disconnect() { setState(network::State::ERROR); return network::Result::RESULT_ERROR; };    
    network::Result Shutdown() { setState(network::State::ERROR); return network::Result::RESULT_ERROR; };
    
    network::Type getType() { return this->type; }; 
};
#endif

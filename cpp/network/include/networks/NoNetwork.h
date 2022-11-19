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

    NoNetwork(const string& address, const uint16_t& port)
        : Network(address, port)
    {};

    ~NoNetwork()
    {};

    network::Result send(const string& buffer) { buffer[0]; return network::Result::RESULT_ERROR; }; // remove data[0], it is to make compiler not to complain because of unused variable
    network::Result reveive(string& buffer) { buffer[0]; return network::Result::RESULT_ERROR; };

    network::Type getType() { return this->type; }; 
};
#endif

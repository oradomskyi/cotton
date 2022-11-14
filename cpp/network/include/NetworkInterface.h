#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <string>
#include "constants.h"

using std::string;

class NetworkInterface
{
public:
    virtual network::Result send(const string& buffer) = 0;
    virtual network::Result receive(string& buffer) = 0;
 
    virtual network::Type getType() = 0;
    virtual network::State getState() = 0;
};
#endif

#ifndef NETWORKTYPEA_H
#define NETWORKTYPEA_H

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>

#include "../Network.h"

using std::cout;
using std::endl;


namespace network
{

class TypeA : public Network
{
private:
    static const network::Type type = network::Type::TYPEA;
public:
    TypeA();
    ~TypeA();

    void connect();
    void write();
    void disconnect();
    network::Type getType() { return this->type; }; 
};

}
#endif

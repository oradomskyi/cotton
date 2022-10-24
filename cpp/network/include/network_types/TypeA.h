#ifndef NETWORKTYPEA_H
#define NETWORKTYPEA_H

#include "../Network.h"

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
    void disconnect();
    network::Type getType() { return this->type; }; 

};

}
#endif

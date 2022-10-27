#ifndef NETWORKTYPEA_H
#define NETWORKTYPEA_H

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>

#include "../Network.h"

using std::cout; // remove when not needed, this is for debug only
using std::endl; // remove when not needed, this is for debug only

class SocketGLIBC : public Network
{
private:
    static const network::Type type = network::Type::SOCKET_GLIBC;

    int m_socket;
    static const int shutdown_mode = 2; // todo move to constants // stop both reception and transmission
public:
    SocketGLIBC();
    ~SocketGLIBC();

    void connect();
    void write();
    void disconnect();
    network::Type getType() { return this->type; }; 
};
#endif

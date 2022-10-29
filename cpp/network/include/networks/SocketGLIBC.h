#ifndef NETWORKTYPEA_H
#define NETWORKTYPEA_H

#include <iostream>

#include <string>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_pton()

#include <stdio.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>


#include "../Network.h"

using std::cout; // remove when not needed, this is for debug only
using std::endl; // remove when not needed, this is for debug only

using std::string;

/*
namespace glibc
{
	int tmp
	//int connect();
	//int connect();
}*/

class SocketGLIBC : public Network
{
private:
    static const network::Type type = network::Type::SOCKET_GLIBC;
    static const int shutdown_mode = 2; // todo move to constants // stop both reception and transmission

	string address;
	uint16_t port;
    int m_socket;
	struct sockaddr_in m_servername;

public:
	SocketGLIBC();
    SocketGLIBC(const string& address, const uint16_t& port);
    ~SocketGLIBC();

    network::Result Create();
    network::Result Resolve();
    network::Result Connect();
    network::Result Write(const string& data);
    network::Result Disconnect();
    network::Result Shutdown();

    network::Type getType() { return this->type; }; 

	void setAddress(const string& address) { this->address = address; };   // not sure this is a good design decision
	void setPort(const uint16_t& port) { this->port = port; }; // not sure this is a good design decision
};
#endif

#ifndef NETWORK_CONSTANTS_H
#define NETWORK_CONSTANTS_H

namespace network
{

enum State {
	  ERROR = -1
  	, READY
	, CONNECTED
	, PENDING
};

enum Type
{
      NO_NETWORK
    , SOCKET_GLIBC
    , OTHER
};

enum SocketState
{
	  SOCKET_ERROR = -1
	, SOCKET_OK = 0
};

} // namespace Network

#endif

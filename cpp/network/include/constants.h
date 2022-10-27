#ifndef NETWORK_CONSTANTS_H
#define NETWORK_CONSTANTS_H

namespace network
{

enum State {
  	  READY
	, CONNECTED
	, PENDING
	, ERROR
};

enum Type
{
      NO_NETWORK
    , SOCKET_GLIBC
    , OTHER
};

} // namespace Network

#endif

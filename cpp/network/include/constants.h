#ifndef NETWORK_CONSTANTS_H
#define NETWORK_CONSTANTS_H

namespace network
{

enum Result {
      RESULT_ERROR = -1
    , RESULT_OK = 0
};

enum State
{
	  ERROR = -1
  	, CREATED
    , HOST_RESOLVED
	, CONNECTED
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

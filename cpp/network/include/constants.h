#ifndef NETWORK_CONSTANTS_H
#define NETWORK_CONSTANTS_H

namespace network
{

enum State {
  	  READY
	, CONNECTED
	, HALT
	, ERROR
};

enum Type
{
      NO_NETWORK
    , TYPEA
    , TYPEB
};

} // namespace Network

#endif

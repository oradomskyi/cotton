#ifndef THREADMASTERCONSTANTS_H
#define THREADMASTERCONSTANTS_H

namespace threadmaster
{

enum State {
  	  PENDING
	, READY
    , RUNNING
    , HALT
	, ERROR
};

enum Type {
	  SERIAL
    , PARALLEL_POSIX
    , PARALLEL_BOOSTFIBER
	, NONE
};

} // threadmaster
#endif

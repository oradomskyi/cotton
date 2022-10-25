#ifndef THREADMASTERINTERFACE_H
#define THREADMASTERINTERFACE_H

#include "constants.h"

class ThreadMasterInterface
{
public:
	virtual void start() = 0;
	virtual void stop() = 0;
    virtual threadmaster::Type getType() = 0;
	virtual threadmaster::State getState() = 0;
};

#endif

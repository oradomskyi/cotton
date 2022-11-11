#ifndef FLOODINTERFACE_H
#define FLOODINTERFACE_H

#include "constants.h"

class FloodInterface
{
public:
	virtual void enable() = 0;
	virtual void run() = 0;
	virtual void disable() = 0;
    virtual flood::RequestType getType() = 0;
	virtual flood::State getState() = 0;
    virtual void operator()() = 0;
};

#endif

#ifndef FLOODINTERFACE_H
#define FLOODINTERFACE_H

#include "constants.h"

class FloodInterface
{
public:
	virtual void start() = 0;
	virtual void stop() = 0;
    virtual flood::RequestType getType() = 0;
	virtual flood::State getState() = 0;
};

#endif

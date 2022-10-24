#ifndef FLOODINTERFACE_H
#define FLOODINTERFACE_H

#include "constants.h"

class FloodInterface
{
protected:
	flood::State state;
	void setState(flood::State new_state);
public:
	virtual void start() = 0;
	virtual void stop() = 0;
	flood::State getState();
};

#endif

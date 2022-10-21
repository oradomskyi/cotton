#ifndef FLOODINTERFACE_H
#define FLOODINTERFACE_H

#include "constants.h"

class FloodInterface
{
protected:
	FloodState state;
	void setState(FloodState new_state);
public:
	virtual void start() = 0;
	virtual void stop() = 0;
	FloodState getState();
};

#endif

#ifndef FLOOD_H
#define FLOOD_H

#include "FloodInterface.h"
#include "Target.h"

class Flood : public FloodInterface
{
protected:
	Target target;
public:
	Flood(string address, uint16_t port);
	Target* getTarget();
};

#endif

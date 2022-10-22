#include "../include/FloodInterface.h"

FloodState FloodInterface::getState() { return this->state; };

void FloodInterface::setState(FloodState new_state)
{
	this->state = new_state;
}

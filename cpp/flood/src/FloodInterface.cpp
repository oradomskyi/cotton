#include "../include/FloodInterface.h"

flood::State FloodInterface::getState() { return this->state; };

void FloodInterface::setState(flood::State new_state)
{
	this->state = new_state;
}

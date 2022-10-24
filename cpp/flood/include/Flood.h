#ifndef FLOOD_H
#define FLOOD_H

#include "FloodInterface.h"
#include "Target.h"
#include "../../network/include/networks.h"

using network::Network;

class Flood : public FloodInterface
{
protected:
	Target target;
	Network* networkPtr;
    flood::State state;

	void initNetwork();
	void setState(flood::State new_state) { this->state = new_state; };
public:
	Flood(string address, uint16_t port);
	~Flood();
	
	Target* getTarget(); // let's keep it modifyable to change it's proxy
	Network* getNetworkPtr(); // change to const if there would be nothing to change in the Network object
    flood::State getState() { return this->state; };
};

#endif

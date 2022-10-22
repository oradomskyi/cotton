#ifndef FLOOD_H
#define FLOOD_H

#include "FloodInterface.h"
#include "Target.h"
#include "../../network/include/Network.h"

using network::Network;

class Flood : public FloodInterface
{
protected:
	Target target;
	Network* networkPtr;
	void initNetwork(/*TODO: implement this */);
public:
	Flood(string address, uint16_t port);
	~Flood();
	
	Target* getTarget(); // let's keep it modifyable to change it's proxy
	Network* getNetworkPtr(); // change to const if there would be nothing to change in the Network object
};

#endif

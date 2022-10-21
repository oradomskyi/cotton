#ifndef TARGET_H
#define TARGET_H

#include "IPPort.h"
#include "Proxy.h"

class Target : public IPPort
{
protected:
	Proxy*  proxy;
public:
	Target(string address, uint16_t port);
	
	Proxy* getProxy();
	void updateProxy();
	void UpdateProxy(string url);
};

#endif

#ifndef TARGET_H
#define TARGET_H

#include "IPPort.h"
#include "Proxy.h"

class Target : public IPPort
{
protected:
	const Proxy* proxyPtr;
public:
	Target(const string& address, const uint16_t& port);
	~Target();
	
	const Proxy* getProxyPtr() const;
	void updateProxy();
	void updateProxy(const Proxy& proxy);
};

#endif

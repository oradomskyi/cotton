#ifndef PROXYMANAGER_H
#define PROXYMANAGER_H

#include <mutex>
#include <time.h>
#include <string>
#include <vector>

// TODO: is a Proxy just an IPPort or something more complicated?
#include "Proxy.h"

using std::mutex;
using std::lock_guard;
using std::string;
using std::vector;
using std::to_string;

class ProxyManager
{
private:
	static ProxyManager* _proxyManager;
	static mutex _mutex;
	
	ProxyManager();
    ~ProxyManager();

	ProxyManager(ProxyManager& other) = delete;
	void operator = (const ProxyManager&) = delete; 
	    
    vector<Proxy> proxies;   
	void loadProxies();
	 
public:
	static ProxyManager* getInstance();
	
	const Proxy& getProxy(string url);
	const Proxy& getRandomProxy(); // return link to one of the proxies we have
	string getRandomIPv4(); // for this one we give away value
};

#endif

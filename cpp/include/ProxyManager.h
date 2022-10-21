#ifndef PROXYMANAGER_H
#define PROXYMANAGER_H

#include <mutex>
#include <string>

// TODO: is a Proxy just an IPPort or something more complicated?
#include "Proxy.h"

using std::mutex;
using std::string;

class ProxyManager()
{
private:
	static ProxyManager* m_proxyManager;
	static mutex m_mutex;
	
protected:
	ProxyManager();
    ~ProxyManager();
    
    vector<Proxy> proxies;   
	void loadProxies();
	 
public:
	ProxyManager(ProxyManager& other) = delete;
	
	void operator = (const ProxyManager&) = delete; 
	
	static ProxyManager* getInstance();
	
	const Proxy& getProxy(string url);
	const Proxy& getRandomProxy();
	const string& getRandomIPv4();
};

#endif

#ifndef PROXYMANAGER_H
#define PROXYMANAGER_H

#include <mutex>
#include <string>
#include <vector>
#include <unordered_set>
#include <time.h>
// TODO: is a Proxy just an IPPort or something more complicated?
#include "Proxy.h"

using std::mutex;
using std::lock_guard;
using std::string;
using std::vector;
using std::unordered_set;
using std::to_string;

class ProxyManager
{
private:
	static ProxyManager* _proxyManager;
	static mutex _mutex;
	
	vector<Proxy>* proxies_vec;
    unordered_set<Proxy, Proxy::HashFunction>* proxies_set;
    
	ProxyManager()
		: proxies_vec(new vector<Proxy>())
	{
		// I belive this constructor is going to be called only once

		// this one is not thread safe and have to bve called only once at the beginning of a program
		srand(time(0)); // init seed
	
		//TODO: implement loading proxies
		this->proxies_vec->insert(this->proxies_vec->end(),
			{
		  	Proxy("proxy1",1)
			, Proxy("proxy2",1)
			, Proxy("proxy3",1)
			, Proxy("proxy4",1) 
			}
		);
		
		this->proxies_set = 
			new unordered_set<Proxy, Proxy::HashFunction>(this->proxies_vec->begin(), this->proxies_vec->end());
	}
	
    ~ProxyManager()
    {
    	this->proxies_vec->~vector();
    	this->proxies_set->~unordered_set();
    };

	ProxyManager(ProxyManager& other) = delete;
	void operator = (const ProxyManager&) = delete; 
	
	void loadProxies();
	 
public:
	static ProxyManager* getInstance();
	
	const Proxy& getProxy(string url);
	const Proxy& getRandomProxy(); // return link to one of the proxies we have
	string getRandomIPv4(); // for this one we give away value
};

#endif

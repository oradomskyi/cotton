#include "../include/ProxyManager.h"

ProxyManager* ProxyManager::_proxyManager = nullptr;
mutex ProxyManager::_mutex;

ProxyManager* ProxyManager::getInstance()
{
	lock_guard<mutex> lock(_mutex);
	if(nullptr == _proxyManager)
	{
		_proxyManager = new ProxyManager();
	}
	return _proxyManager;
}

ProxyManager::ProxyManager()
{
	// this one is not thread safe and have to bve called only once at the beginning of a program
	srand(time(0)); // init seed
	
	//TODO: implement loading proxies
	this->proxies = {
		 Proxy("proxy1",1)
		,Proxy("proxy2",1)
		,Proxy("proxy3",1)
		,Proxy("proxy4",1) 
	};
}
	

const Proxy& ProxyManager::getRandomProxy()
{
	return this->proxies[rand() % this->proxies.size()];
}

string ProxyManager::getRandomIPv4()
{
	// TODO: this is damn slow, find a better implementation	
	return to_string(rand()%255)+'.'
		+ to_string(rand()%255)+'.'
		+ to_string(rand()%255)+'.'
		+ to_string(rand()%255); 
}

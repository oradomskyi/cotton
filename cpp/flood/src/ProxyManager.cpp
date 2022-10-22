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

const Proxy& ProxyManager::getRandomProxy()
{
	return this->proxies_vec->at(rand() % this->proxies_vec->size());
}

string ProxyManager::getRandomIPv4()
{
	// TODO: this is damn slow, find a better implementation	
	return to_string(rand()%255)+'.'
		+ to_string(rand()%255)+'.'
		+ to_string(rand()%255)+'.'
		+ to_string(rand()%255); 
}

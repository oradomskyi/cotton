#include <iostream>

#include "include/methods/allmethods.h"

using std::string;
using std::cout;
using std::endl;

void test_memory_create_destroy()
{
	for(int i = 0; i < 1000000; i++)
	{
		MethodGET attacker(string("1.2.3.4"), 5678);
		attacker.start();
		attacker.stop();
	}
}

void test_init_attacker()
{
	cout << endl;
	MethodGET attacker(string("1.2.3.4"), 5678);
	
	cout <<  "target=" << attacker.getTarget()->getAddress() 
		<< ":" << attacker.getTarget()->getPort() 
		<< " proxy="<< attacker.getTarget()->getProxyPtr()->getAddress() << ":"<< attacker.getTarget()->getProxyPtr()->getPort()
		<<" attacker state=" << attacker.getState()
		<< endl;
		
	cout << "header=" << attacker.getHeader() << endl;
	cout << "request=" << attacker.getRequest() << endl;
	
	attacker.start();
	
	cout <<" called start(), state=" << attacker.getState() << endl;
	
	attacker.stop();
	
	cout <<" called stop(), state=" << attacker.getState() << endl;
	
}

int main()
{
	test_memory_create_destroy();

	return 0;
}

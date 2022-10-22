#include <iostream>

#include "include/methods/allmethods.h"

using std::string;
using std::cout;
using std::endl;

void test_check_Proxy_security()
{
	// if you uncomment the below
	// expected behavior code not able to compile with
	// error: assignment of read-only location 
	
	/*
	MethodGET attacker(string("1.2.3.4"), 5678); // create attacker
	attacker.getTarget()->getProxyPtr()->getAddress() = string("yeyeye"); // trying to assign read-only address
	attacker.getTarget()->getProxyPtr()->getPort() = 777; // trying to assign read-only port
	*/
}

void test_check_Target_security()
{
	// if you uncomment the below
	// expected behavior code not able to compile with
	// error: assignment of read-only location 
	/*
	MethodGET attacker(string("1.2.3.4"), 5678);
	attacker.getTarget()->getAddress() = string("yeyeye"); // trying to assign read-only address
	attacker.getTarget()->getPort() = 777; // trying to assign read-only port
	*/
}

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
	//test_memory_create_destroy();

	test_check_Target_security();
	test_check_Proxy_security();

	return 0;
}

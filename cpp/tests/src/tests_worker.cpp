#include "../include/tests_worker.h"

void test_check_Proxy_security()
{
	// if you uncomment the below
	// expected behavior code not able to compile with
	// error: assignment of read-only location 
	
	/*
	GET attacker(string("1.2.3.4"), 5678); // create attacker
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
	GET attacker(string("1.2.3.4"), 5678);
	attacker.getTarget()->getAddress() = string("yeyeye"); // trying to assign read-only address
	attacker.getTarget()->getPort() = 777; // trying to assign read-only port
	*/
}

void test_memory_create_destroy()
{
	// expected behavior is that occupied memory stays constant
	for(int i = 0; i < 1000000; i++)
	{
		GET attacker(string("1.2.3.4"), 5678);
		attacker.start();
		attacker.stop();
	}
}

void test_create_worker()
{
	cout << endl;
	GET attacker(string("1.2.3.4"), 5678);
	
	cout <<  endl <<"target=" << attacker.getTarget()->getAddress() 
		<< ":" << attacker.getTarget()->getPort() 
		<< endl <<" proxy="<< attacker.getTarget()->getProxyPtr()->getAddress() << ":"<< attacker.getTarget()->getProxyPtr()->getPort()
		<< endl <<" attacker state=" << attacker.getState()
		<< endl;
		
	cout << endl <<"header=" << attacker.getHeader() << endl;
	cout << endl <<"request=" << attacker.getRequest() << endl;
	cout << endl <<"networkState=" << attacker.getNetworkPtr()->getState() << endl;
	
	attacker.getNetworkPtr()->Connect();
	cout << endl <<"called Network::connect(), networkState=" << attacker.getNetworkPtr()->getState() << endl;
	attacker.getNetworkPtr()->Disconnect();
	cout << endl <<"called Network::disconnect(), networkState=" << attacker.getNetworkPtr()->getState() << endl;
	
	
	attacker.start();
	cout <<endl <<" called start(), state=" << attacker.getState() << endl;
	
	attacker.stop();
	cout <<endl <<" called stop(), state=" << attacker.getState() << endl;
	
}

void test_init_worker()
{
	test_create_worker();
	test_create_worker();
	test_create_worker();
}

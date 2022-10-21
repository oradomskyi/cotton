#include <iostream>

#include "include/methods/allmethods.h"

using std::string;
using std::cout;
using std::endl;

int main()
{
	/*
	string url = "1.2.3.4";
	uint16_t port = 1234;
	Target t(url, port);
	std::cout <<  t.getAddress() << ":" << t.getPort();
	*/
	
	MethodGET attacker(string("1.2.3.4"), 5678);
	
	cout <<  "target=" << attacker.getTarget()->getAddress() 
		<< ":" << attacker.getTarget()->getPort() 
		<< " proxy="<< attacker.getTarget()->getProxy()->getAddress() << ":"<< attacker.getTarget()->getProxy()->getPort()
		<<" attacker state=" << attacker.getState()
		<< endl;
		
	cout << "header=" << attacker.getHeader() << endl;
	cout << "request=" << attacker.getRequest() << endl;
	
	attacker.start();
	
	cout <<" called start(), state=" << attacker.getState() << endl;
	
	attacker.stop();
	
	cout <<" called stop(), state=" << attacker.getState() << endl;
	
	return 0;
}

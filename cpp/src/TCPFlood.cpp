#include "../include/TCPFlood.h"

TCPFlood::TCPFlood(string address, uint16_t port)
	: Flood(address, port)
{
	this->createHeader();
	this->createRequest();
}

string& TCPFlood::getHeader() { return this->header; }

string& TCPFlood::getRequest() { return this->request; }

void TCPFlood::createHeader()
{
	this->header = "TCPFlood header";
}

void TCPFlood::createRequest()
{
	this->request = "TCPFlood request";
}

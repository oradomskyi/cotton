#ifndef IPPORT_H
#define IPPORT_H

#include <string>
#include <functional>

using std::string;
using std::hash;
using std::to_string;

class IPPort
{
protected:
	string address;
	uint16_t port;
public:
	IPPort()
		:address("")
		,port(0)
	{};

	IPPort(string address, uint16_t port)
		:address(address)
		,port(port)
	{};

	IPPort(const IPPort& other)
		:address(other.address)
		,port(other.port)
	{};
	
	const string& getAddress() const { return this->address; };
	const uint16_t& getPort() const { return this->port; };
	string toString() { return this->address + ":" + to_string(this->port); };
	
	bool operator == (const IPPort& other) const
	{
		return (0 == address.compare(other.address)) && (port == other.port); 
	}
	
	struct HashFunction
	{
		size_t operator () (const IPPort& ipport) const
		{
			size_t hash_address = hash<string>()(ipport.address);
			size_t hash_port = hash<uint16_t>()(ipport.port);
			
			return hash_address ^ hash_port;
		}
	};
};

#endif

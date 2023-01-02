#include <gtest/gtest.h>
#include "../../../../cpp/flood/include/Flood.h"

TEST(Flood, Flood_ConstructorArgs)
{
	string address = "1.1.1.1";
	uint16_t port = 1;
	Flood flood(address, port);

	// has initialized Target
	EXPECT_EQ(address, flood.getTarget()->getAddress()); // Target has Address
	EXPECT_EQ(port, flood.getTarget()->getPort()); // Target has Port
	EXPECT_EQ(nullptr, flood.getNetworkPtr());  // has no network
	EXPECT_EQ(flood::State::ERROR, flood.getState());  // state is ERROR          
}

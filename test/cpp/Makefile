CC := g++
CFLAGS = -Wall -W -Werror -O0 -std=c++14 -pthread
BOOSTFLAGS = -lboost_coroutine -lboost_context  -lboost_system -lboost_fiber

GTEST_INCLUDE = googletest/googletest/include/
GTEST_LIB = googletest/build/lib/libgtest.a
GTEST_MAIN = googletest/build/lib/libgtest_main.a

GTESTFLAGS = -lgtest

PREFIX_SRC = ../../cpp/

DIR_BOOST_INCLUDE = ./$(PREFIX_SRC)3rdParty/boost/include/
DIR_BOOST_LIB = ./$(PREFIX_SRC)3rdParty/boost/lib/

DIR_SRC_FLOOD = flood/src/
DIR_SRC_FLOOD_METHODS = flood/src/methods/
DIR_SRC_NETWORK = network/src/
DIR_SRC_NETWORK_NETWORKS = network/src/networks/
DIR_SRC_THREADMASTER = threadmaster/src/
DIR_SRC_THREADMASTER_MASTERS = threadmaster/src/masters/
#DIR_SRC_TESTS = tests/src/

SRC_ALL = $(PREFIX_SRC)$(DIR_SRC_FLOOD)*.cpp $(PREFIX_SRC)$(DIR_SRC_FLOOD_METHODS)*.cpp $(PREFIX_SRC)$(DIR_SRC_NETWORK)*.cpp $(PREFIX_SRC)$(DIR_SRC_NETWORK_NETWORKS)*.cpp $(PREFIX_SRC)$(DIR_SRC_THREADMASTER)*.cpp $(PREFIX_SRC)$(DIR_SRC_THREADMASTER_MASTERS)*.cpp 

#$(PREFIX_SRC)$(DIR_SRC_TESTS)*.cpp

SRC_TEST_ALL = $(DIR_SRC_FLOOD)*.cpp 

#$(DIR_SRC_FLOOD_METHODS)*.cpp $(DIR_SRC_NETWORK)*.cpp $(DIR_SRC_NETWORK_NETWORKS)*.cpp $(DIR_SRC_THREADMASTER)*.cpp $(DIR_SRC_THREADMASTER_MASTERS)*.cpp $(DIR_SRC_TESTS)*.cpp

TARGET = test

all: $(TARGET)

$(TARGET): main.cpp $(SRC_TEST_ALL)
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp $(SRC_TEST_ALL) $(SRC_ALL) -I$(DIR_BOOST_INCLUDE) -I$(GTEST_INCLUDE) -L$(GTEST_LIB) -L$(DIR_BOOST_LIB) $(BOOSTFLAGS) $(GTESTFLAGS)

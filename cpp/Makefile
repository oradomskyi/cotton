# g++ -Wall -W -Werror main.cpp flood/src/*.cpp flood/src/methods/*.cpp network/src/*.cpp tests/src/*.cpp -o tool -O0

CC := g++
CFLAGS = -Wall -W -O0 -std=c++14 -pthread
BOOSTFLAGS = -lboost_coroutine -lboost_context -lboost_system -lboost_fiber -lboost_url


DIR_BOOST_INCLUDE = /usr/local/include/boost #./3rdParty/boost/include/
DIR_BOOST_LIB = /usr/local/lib
#./3rdParty/boost/libs/

DIR_SRC_CLIENT = client/src/
DIR_SRC_METHODS = methods/src/
#DIR_SRC_FLOOD = flood/src/
#DIR_SRC_FLOOD_METHODS = flood/src/methods/
#DIR_SRC_NETWORK = network/src/
#DIR_SRC_NETWORK_NETWORKS = network/src/networks/
#DIR_SRC_THREADMASTER = threadmaster/src/
#DIR_SRC_THREADMASTER_MASTERS = threadmaster/src/masters/
#DIR_SRC_TESTS = tests/src/

SRC_ALL = $(DIR_SRC_CLIENT)*.cpp $(DIR_SRC_METHODS)*.cpp
#$(DIR_SRC_FLOOD)*.cpp $(DIR_SRC_FLOOD_METHODS)*.cpp $(DIR_SRC_NETWORK)*.cpp $(DIR_SRC_NETWORK_NETWORKS)*.cpp $(DIR_SRC_THREADMASTER)*.cpp $(DIR_SRC_THREADMASTER_MASTERS)*.cpp $(DIR_SRC_TESTS)*.cpp

TARGET = tool

all: $(TARGET)

#-I$(DIR_BOOST_INCLUDE) -L$(DIR_BOOST_LIB)  $(SRC_ALL)
$(TARGET): main.cpp $(SRC_ALL)
	$(CC) $(CFLAGS) -I$(DIR_BOOST_INCLUDE) main.cpp  $(SRC_ALL) -o $(TARGET) -L$(DIR_BOOST_LIB) $(BOOSTFLAGS)
	#g++ -I/usr/local/include/boost main.cpp -o tool -L/usr/local/lib -lboost_coroutine -lboost_context -lboost_system -lboost_fiber 
	#
#
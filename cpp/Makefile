# g++ -Wall -W -Werror main.cpp flood/src/*.cpp flood/src/methods/*.cpp network/src/*.cpp tests/src/*.cpp -o tool -O0

CC := g++
CFLAGS = -Wall -W -Werror -O0 -std=c++14

DIR_SRC_FLOOD = flood/src/
DIR_SRC_FLOOD_METHODS = flood/src/methods/
DIR_SRC_NETWORK = network/src/
DIR_SRC_NETWORK_NETWORKS = network/src/networks/
DIR_SRC_THREADMASTER = threadmaster/src/
DIR_SRC_THREADMASTER_MASTERS = threadmaster/src/masters/
DIR_SRC_TESTS = tests/src/

SRC_ALL = $(DIR_SRC_FLOOD)*.cpp $(DIR_SRC_FLOOD_METHODS)*.cpp $(DIR_SRC_NETWORK)*.cpp $(DIR_SRC_NETWORK_NETWORKS)*.cpp $(DIR_SRC_THREADMASTER)*.cpp $(DIR_SRC_THREADMASTER_MASTERS)*.cpp $(DIR_SRC_TESTS)*.cpp

TARGET = tool

all: $(TARGET)
$(TARGET): main.cpp $(SRC_ALL)
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp $(SRC_ALL)

# g++ -Wall -W -Werror main.cpp flood/src/*.cpp flood/src/methods/*.cpp network/src/*.cpp tests/src/*.cpp -o tool -O0

CC := g++
CFLAGS = -Wall -W -Werror -O0 -std=c++14

DIR_SRC_FLOOD = flood/src/
DIR_SRC_FLOOD_METHODS = flood/src/methods/
DIR_SRC_NETWORK = network/src/
DIR_SRC_TESTS = tests/src/

TARGET = tool

all: $(TARGET)
$(TARGET): main.cpp $(DIR_SRC_FLOOD)*.cpp $(DIR_SRC_FLOOD_METHODS)*.cpp $(DIR_SRC_NETWORK)*.cpp $(DIR_SRC_TESTS)*.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp $(DIR_SRC_FLOOD)*.cpp $(DIR_SRC_FLOOD_METHODS)*.cpp $(DIR_SRC_NETWORK)*.cpp $(DIR_SRC_TESTS)*.cpp

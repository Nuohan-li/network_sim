
all: main.cpp router.cpp network.cpp terminal.cpp port.cpp
	g++ -std=c++11 -Wall main.cpp network.cpp router.cpp terminal.cpp port.cpp



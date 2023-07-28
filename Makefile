
all: main.cpp router.cpp network.cpp terminal.cpp
	g++ -std=c++11 -Wall main.cpp network.cpp router.cpp terminal.cpp



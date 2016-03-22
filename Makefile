hexadiff: hexadiff.cpp
	g++ hexadiff.cpp -o hexadiff -std=c++11

install:
	cp hexadiff /usr/bin/

hexadiff: hexadiff.cpp
	g++ hexadiff.cpp -o hexadiff -std=c++11 -g

install: hexadiff
	cp hexadiff /usr/bin/

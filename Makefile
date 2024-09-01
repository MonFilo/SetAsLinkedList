main.exe: main.o myexcp.o
	g++ main.o myexcp.o -o main.exe -std=c++0x

main.o: main.cpp set.h
	g++ -c main.cpp -o main.o -std=c++0x

myexcp.o: myexcp.cpp
	g++ -c myexcp.cpp -o myexcp.o -std=c++0x
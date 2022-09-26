darts: main.o fraction.o point.o
	g++ -o darts main.o fraction.o point.o

main.o: main.cpp point.h fraction.h
	g++ -c main.cpp

fraction.o: fraction.cpp fraction.h
	g++ -c fraction.cpp

point.o: point.cpp point.h fraction.h
	g++ -c point.cpp

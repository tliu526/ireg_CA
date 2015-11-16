all: first ;

first: first.cpp
	g++ -Wall -o first first.cpp 

clean:
	rm -f *.exe

DGG: DelaunayGridGenerator.cpp
	g++ -g -o DGG -std=c++11 DelaunayGridGenerator.cpp Cell.cpp GridGenerator.cpp util.cpp Tri.cpp Poly.cpp Edge.cpp Point.cpp
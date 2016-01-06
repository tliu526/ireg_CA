clean:
	rm -f *.exe

DGG: DelaunayGridGenerator.cpp
	g++ -g -o DGG -std=c++11 DelaunayGridGenerator.cpp Cell.cpp GridGenerator.cpp util.cpp Tri.cpp Poly.cpp Edge.cpp Point.cpp

VGG: VoronoiGridGenerator.cpp
	g++ -g -o VGG -std=c++11 VoronoiGridGenerator.cpp Cell.cpp GridGenerator.cpp util.cpp Tri.cpp Poly.cpp Edge.cpp Point.cpp

util: util.cpp
	g++ -g -o util -std=c++11 util.cpp Tri.cpp Point.cpp Edge.cpp

Simulator: Simulator.cpp
	g++ -g -o Simulator -std=c++11 DelaunayGridGenerator.cpp Cell.cpp GridGenerator.cpp util.cpp Tri.cpp Poly.cpp Edge.cpp Point.cpp RuleTable.cpp Simulator.cpp SimpleMajorityRule.cpp
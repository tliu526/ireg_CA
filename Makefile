clean:
	rm -f *.exe *.out

DGG: DelaunayGridGenerator.cpp
	g++ -g -o DGG.out -std=c++11 DelaunayGridGenerator.cpp Cell.cpp GridGenerator.cpp util.cpp Tri.cpp Poly.cpp Edge.cpp Point.cpp Property.cpp

VGG: VoronoiGridGenerator.cpp
	g++ -g -o VGG.out -std=c++11 VoronoiGridGenerator.cpp Cell.cpp GridGenerator.cpp util.cpp Tri.cpp Poly.cpp Edge.cpp Point.cpp Property.cpp

util: util.cpp
	g++ -g -o util.out -std=c++11 util.cpp Tri.cpp Point.cpp Edge.cpp

Simulator: Simulator.cpp
	g++ -g -o Simulator.out -std=c++11 DelaunayGridGenerator.cpp Cell.cpp GridGenerator.cpp util.cpp Tri.cpp Poly.cpp Edge.cpp Point.cpp RuleTable.cpp Simulator.cpp SimpleMajorityRule.cpp Stencil.cpp Property.cpp
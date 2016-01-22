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

LMBaseline: LMBaseline.cpp
	g++ -g -o LMBaseline.out -std=c++11 DelaunayGridGenerator.cpp Cell.cpp GridGenerator.cpp util.cpp Tri.cpp Poly.cpp Edge.cpp Point.cpp RuleTable.cpp Simulator.cpp SimpleMajorityRule.cpp Stencil.cpp Property.cpp LMBaseline.cpp BinaryRuleTable.cpp

RGG: RegularGridGenerator.cpp
	g++ -g -o RGG.out -std=c++11 RegularGridGenerator.cpp Cell.cpp GridGenerator.cpp util.cpp Tri.cpp Poly.cpp Edge.cpp Point.cpp Property.cpp

LMReg: LMReg.cpp
	g++ -g -o LMReg.out -std=c++11 RegularGridGenerator.cpp Cell.cpp GridGenerator.cpp util.cpp Tri.cpp Poly.cpp Edge.cpp Point.cpp RuleTable.cpp Simulator.cpp SimpleMajorityRule.cpp Stencil.cpp Property.cpp LMReg.cpp BinaryRuleTable.cpp

AshLife: AshLife.cpp
	g++ -g -o AshLife.out -std=c++11 DelaunayGridGenerator.cpp Cell.cpp GridGenerator.cpp util.cpp Tri.cpp Poly.cpp Edge.cpp Point.cpp RuleTable.cpp Simulator.cpp Stencil.cpp Property.cpp BinaryRuleTable.cpp SimpleLifeRule.cpp AshLife.cpp VertStencil.cpp

Main: main.cpp
	g++ -g -o Main.out -std=c++11 *.cpp Experiment.h PenroseLifeVert22.h ClockwiseComp.h DistComp.h PenroseAsh.h
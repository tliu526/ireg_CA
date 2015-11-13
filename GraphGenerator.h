/*
An abstract class for generating graphs.

(c) Tony Liu 2015.
*/
#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include "util.h"
#include "Graph.h"

#include <vector>
#include <string>

class GraphGenerator {
public:
	GraphGenerator(std::vector<point>& p);

	virtual void generate_graph() = 0;
	void graph_to_file(std::string f);
	
protected:
	std::vector<std::point> points;
	//TODO?
	Graph<std::string> g;
};

#endif
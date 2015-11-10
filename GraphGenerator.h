/*
An abstract class for generating graphs.

(c) Tony Liu 2015.
*/
#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include "util.h"
#include "Cell.h"
#include "Graph.h"

#include <string>

using namespace std;

//typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Cell> Graph; // boost definition of adjacency list

class GraphGenerator {
public:
	GraphGenerator(vector<point>& p);

	virtual void generate_graph() = 0;
	void graph_to_file(string f);
	
protected:
	vector<point> points;
	Graph g;
};

#endif
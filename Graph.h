/*
A graph implementation that utilizes adjacency lists, as the graphs will be relatively sparse. Currently the 
graph is undirected.

Things to think about:
- Do we need edge labels? (probably not)

(c) 2015 Tony Liu.
*/
#ifndef GRAPH_H
#define GRAPH_H

#include "util.h"
#include "Cell.h"

#include <list>
#include <map>
#include <string>

using namespace std;

class Graph {
public:
	int add_vertex(point& p); // returns the label
	void remove_vertex(int id); 
	void add_edge(int id1, int id2);
	void remove_edge(int id1, int id2);

	void print_adj_list(); // for debugging purposes

protected:
	map<int, Cell> dict; // tracks our vertices (Cells)
};

#endif 
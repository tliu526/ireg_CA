/*
Implementing the adjacency list graph.

(c) 2015 Tony Liu.
*/

#include "Graph.h"

#include <iostream>

using namespace std;

int Graph::add_vertex(point &p){
	Cell c(p);
	int uid = c.get_uid();

	dict.insert(pair<int,Cell>(uid, c));
	//dict[uid] = c;

	return uid;
}

void Graph::remove_vertex(int id){
	if (dict.count(id) == 1){
		dict.erase(id);
	}
}

void Graph::add_edge(int id1, int id2){
	if ((dict.count(id1) == 1) && (dict.count(id2) == 1)) {
		//we're undirected, so need to add to each other's neighbor list
		Cell cell1 = dict[id1];
		Cell cell2 = dict[id2];

		cell1.add_neighbor(id2);
		cell2.add_neighbor(id1);
	}
}

void Graph::remove_edge(int id1, int id2){
	if ((dict.count(id1) == 1) && (dict.count(id2) == 1)) {
		//we're undirected, so need to add to each other's neighbor list
		Cell cell1 = dict[id1];
		Cell cell2 = dict[id2];

		cell1.remove_neighbor(id2);
		cell2.remove_neighbor(id1);
	}
}

void Graph::print_adj_list() {
	map<int, Cell>::iterator map_it;
	for (map_it = dict.begin(); map_it != dict.end(); map_it++) {
		cout << map_it->first;

		Cell c = map_it->second;

		list<int>::iterator list_it;
		for (list_it = c.get_neighbors()->begin(); list_it != c.get_neighbors()->end(); list_it++) {
			cout << "->" << *list_it;
		}
	}
}

//debugging
int main() {
	point p(5.0f, 0.1f);
	Graph g;

	int a = g.add_vertex(p);
	int b = g.add_vertex(p);
	int c = g.add_vertex(p);
	int d = g.add_vertex(p);

	g.add_edge(a,b);
	g.add_edge(b,c);
	g.add_edge(c,d);
	g.add_edge(d,a);

	g.print_adj_list();
}
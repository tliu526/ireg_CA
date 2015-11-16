/*
A graph implementation that utilizes adjacency lists, as the graphs will be relatively sparse. Currently the 
graph is undirected.

TODO: hang an additional template object for holding additional information, such as a cell.
http://stackoverflow.com/questions/5545948/how-to-avoid-repeating-class-name-and-template-call-in-implementation

(c) 2015 Tony Liu.
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <string>
#include <list>

template<class T, class D>
class Graph {
public:
	T add_vertex(T label, D data); // returns the label
	void remove_vertex(T label); 
	void add_edge(T label1, T label2);
	void remove_edge(T label1, T label2);

	void print_adj_list(); // for debugging purposes

private:
	class Vertex { //nested vertex class
	public:
	  Vertex () {};
	  Vertex (T label, D dat);
	  
	  T            get_label();    
	  D            get_data();
	  void         add_neighbor(T label);
	  void         remove_neighbor(T label);
	  std::list<T> *get_neighbors();
	private:
	  T label;
	  D data;
	  std::list<T> neighbors;
	};

	std::map<T, Vertex> dict;
};

#endif 

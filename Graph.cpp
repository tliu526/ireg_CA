/*
Implementing the adjacency list graph.

(c) 2015 Tony Liu.
*/

#include "Graph.h"

#include <iostream>

using namespace std;

template<class T>
T Graph<T>::add_vertex(T label) {

  if(dict.count(label) == 0) { //we need to add the vertex to the graph
    Vertex v(label);
    dict[label] = v;
  }
  return label;
}

template<class T>
void Graph<T>::remove_vertex(T label){
  if (dict.count(label) == 1){
    dict.erase(label);
  }
}

template<class T>
void Graph<T>::add_edge(T label1, T label2){
  if ((dict.count(label1) == 1) && (dict.count(label2) == 1)) {
    //we're undirected, so need to add to each other's neighbor list
    dict[label1].add_neighbor(label2);
    dict[label2].add_neighbor(label1);
  }
}

template<class T>
void Graph<T>::remove_edge(T label1, T label2){
  if ((dict.count(label1) == 1) && (dict.count(label2) == 1)) {
    //we're undirected, so need to add to each other's neighbor list
    dict[label1].remove_neighbor(label2);
    dict[label2].remove_neighbor(label1);
  }
}

template<class T>
void Graph<T>::print_adj_list() {
  typename map<T, Vertex>::iterator map_it;
      for (map_it = dict.begin(); map_it != dict.end(); map_it++) {
	cout << map_it->first;
	
	Vertex v = map_it->second;
	
	typename list<T>::iterator list_it;
	for (list_it = v.get_neighbors()->begin(); list_it != v.get_neighbors()->end(); list_it++) {
	  cout << "->" << *list_it;
	}
	
	cout << '\n';
      }
}

/**** VERTEX IMPLEMENTATION ****/

template<class T>
Graph<T>::Vertex::Vertex(T l) {
  label = l;
}

template<class T>
T Graph<T>::Vertex::get_label(){
  return label;
}

template<class T>
void Graph<T>::Vertex::add_neighbor(T label) {
  neighbors.push_back(label);
}

template<class T>
void Graph<T>::Vertex::remove_neighbor(T label) {
  neighbors.remove(label);
}

template<class T>
list<T> *Graph<T>::Vertex::get_neighbors() {
  return &neighbors;
}

//debugging
int main() {
	Graph<int> g;

	int a = g.add_vertex(1);
	int b = g.add_vertex(2);
	int c = g.add_vertex(3);
	int d = g.add_vertex(4);

	g.add_edge(a,b);
	g.add_edge(b,c);
	g.add_edge(c,d);
	g.add_edge(d,a);

	g.print_adj_list();
}

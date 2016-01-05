/*
A graph implementation that utilizes adjacency lists, as the graphs will be relatively sparse. Currently the 
graph is undirected.

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
    
    std::list<T> *get_neighbors(T label);
    D             get_data(T label);

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

#include "Graph.tpp"

#endif 

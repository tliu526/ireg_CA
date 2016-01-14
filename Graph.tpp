/*
Implementing the adjacency list graph.

(c) 2015 Tony Liu.
*/

#include <iostream>

using namespace std;

template<class T, class D>
T Graph<T,D>::add_vertex(T label, D data) {

  if(dict.count(label) == 0) { //we need to add the vertex to the graph
    Vertex v(label, data);
    dict[label] = v;
  }
  return label;
}

template<class T, class D>
void Graph<T,D>::remove_vertex(T label){
  if (dict.count(label) == 1){
    dict.erase(label);
  }
}

template<class T, class D>
void Graph<T,D>::add_edge(T label1, T label2){
  if ((dict.count(label1) == 1) && (dict.count(label2) == 1)) {
    //we're undirected, so need to add to each other's neighbor list
    dict[label1].add_neighbor(label2);
    dict[label2].add_neighbor(label1);
  }
}

template<class T, class D>
void Graph<T,D>::remove_edge(T label1, T label2){
  if ((dict.count(label1) == 1) && (dict.count(label2) == 1)) {
    //we're undirected, so need to add to each other's neighbor list
    dict[label1].remove_neighbor(label2);
    dict[label2].remove_neighbor(label1);
  }
}

template<class T, class D>
void Graph<T,D>::print_adj_list() {

    float avg = 0;
    typename map<T, Vertex>::iterator map_it;
    for (map_it = dict.begin(); map_it != dict.end(); map_it++) {
        cout << map_it->first;

        Vertex v = map_it->second;

        avg += v.get_neighbors()->size();
        typename list<T>::iterator list_it;
        for (list_it = v.get_neighbors()->begin(); list_it != v.get_neighbors()->end(); list_it++) {
         cout << "->" << *list_it;
       }

       cout << endl;
    }
    cout << "Average degree: " << avg / dict.size() << endl;
}

template<class T, class D>
D* Graph<T,D>::get_data(T label){
  return dict[label].get_data();
}

template<class T, class D>
list<T> *Graph<T,D>::get_neighbors(T label){
  return dict[label].get_neighbors();
}

template<class T, class D>
vector<T> Graph<T,D>::get_vert_labels(){
    vector<T> labels;

    typename map<T, Vertex>::iterator dict_it;
    for(dict_it = dict.begin(); dict_it != dict.end(); dict_it++){
        labels.push_back(dict_it->first);
    }

    return labels;
}

/**** VERTEX IMPLEMENTATION ****/

template<class T, class D>
Graph<T,D>::Vertex::Vertex(T l, D d) {
  label = l;
  data = d;
}

template<class T, class D>
T Graph<T,D>::Vertex::get_label(){
  return label;
}

template<class T, class D>
D* Graph<T,D>::Vertex::get_data() {
  return &data;
}

template<class T, class D>
void Graph<T,D>::Vertex::add_neighbor(T label) {
  if(count(neighbors.begin(), neighbors.end(), label) == 0) {
    neighbors.push_back(label);
  }
}

template<class T, class D>
void Graph<T,D>::Vertex::remove_neighbor(T label) {
  if(count(neighbors.begin(), neighbors.end(), label) > 0) {
    neighbors.remove(label);
  }
}

template<class T, class D>
list<T> *Graph<T,D>::Vertex::get_neighbors() {
  return &neighbors;
}

/*
//debugging
int main() {
    Graph<int, int> g;

    int a = g.add_vertex(1,2);
    int b = g.add_vertex(2,2);
    int c = g.add_vertex(3,2);
    int d = g.add_vertex(4,2);

    g.add_edge(a,b);
    g.add_edge(b,c);
    g.add_edge(c,d);
    g.add_edge(d,a);

    g.print_adj_list();
}
*/
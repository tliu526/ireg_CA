/**
Implementation of VertStencil class.

(c) 2016 Tony Liu.
*/

#include "VertStencil.h"

VertStencil::VertStencil(Graph<string, Cell>* g, GridGenerator* gen) {
    graph = g;
    generator = gen;
    type = OTHER;

    initialize();
}

//checks neighbors of neighbors for all vertices
void VertStencil::initialize() {
    generator->map_faces();

    vector<string> labels = graph->get_vert_labels();

    for(size_t i = 0; i < labels.size(); i++){
        vector<string> adjacent_cells;
        list<string> *neighbors = graph->get_neighbors(labels[i]);
        vector<string> close_cells{begin(*neighbors), end(*neighbors)};
        vector<string> copy = close_cells;

        string cur_label = labels[i];
        //initialize close cells, neighbors of neighbors
        for(size_t j = 0; j < copy.size(); j++){
            list<string> *n_neighbor = graph->get_neighbors(copy[j]);

            typename list<string>::iterator list_it;
            for(list_it = n_neighbor->begin(); list_it != n_neighbor->end(); list_it++) {
                if(count(close_cells.begin(), close_cells.end(), *list_it) == 0) {
                    close_cells.push_back(*list_it);
                }
            }
        }

        //check close cells
        Poly face = generator->face_map[generator->gen_pt_face_map[labels[i]]]; 
        for(size_t cell_i = 0; cell_i < close_cells.size(); cell_i++) {
            string cur_cell = close_cells[cell_i];

            //not including the center cell we're considering
            if(cur_cell.compare(cur_label) != 0){
                if(face.shares_vert(generator->face_map[(generator->gen_pt_face_map)[cur_cell]])){ 
                    adjacent_cells.push_back(cur_cell);
                    graph->add_edge(cur_label, cur_cell);
                }
            }
        }

        neighbor_map[cur_label] = adjacent_cells;
    }
}
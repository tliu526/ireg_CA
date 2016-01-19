/**
An implementation of the Moore Stencil.

(c) 2016 Tony Liu.
*/

#include "MooreStencil.h"
#include "ClockwiseComp.h"

#include <algorithm>

using namespace std;

MooreStencil::MooreStencil(Graph<string, Cell>* g, GridGenerator* gen){
   graph = g;
   generator = gen;
   type = MOORE;

   initialize();   
}

void MooreStencil::initialize() {
    vector<string> labels = graph->get_vert_labels();

    for(size_t i = 0; i < labels.size(); i++){
        string cur_label = labels[i];
        list<string> *neighbors = graph->get_neighbors(cur_label);
        vector<Point> pts;
        vector<string> neighborhood;

        typename list<string>::iterator list_it;
        for(list_it = neighbors->begin(); list_it != neighbors->end(); list_it++) {
            pts.push_back(graph->get_data(*list_it)->get_point());
        }

        Point center_pt = graph->get_data(cur_label)->get_point();
        ClockwiseComp comp(center_pt);
        sort(pts.begin(), pts.end(), comp);

        for(size_t pt_i = 0; pt_i < pts.size(); pt_i++){
            neighborhood.push_back(generator->rev_gen_pt_map[pts[pt_i]]);
        }

        neighbor_map[cur_label] = neighborhood;
    }
}
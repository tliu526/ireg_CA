/**
An experiment template for metrics on the connectivity of a particular grid layout.

NOTE: the "neighborhood" does not include the center cell.

(c) 2016 Tony Liu.
*/

#ifndef CONNECTIVITYEXPR_H
#define CONNECTIVITYEXPR_H

#include "Experiment.h"

#include <fstream>

using namespace std;

class ConnectivityExpr : public Experiment {
    public:
        ConnectivityExpr(string in, string out)
        : grid_file(in), output(out) /**stencil(sten)**/ {};

        void run() {
            GridGenerator gen(grid_file);
            VertStencil vs(gen.get_graph(), &gen);

            fstream file;
            file.open(output, fstream::in | fstream::out | fstream::app);
            file << "NeighborhoodSize" << " " << "Count" << endl;

            map<int,int> neighbor_counts;
            vector<string> labels = gen.get_graph()->get_vert_labels();
            for(size_t i = 0; i < labels.size(); i++) {
                vector<string> *neighborhood = vs.get_neighbors(labels[i]);
                int n_size = neighborhood->size();

                if(neighbor_counts.count(n_size) == 0){
                    neighbor_counts[n_size] = 0;
                }
                neighbor_counts[n_size] += 1;
            }

            typename map<int,int>::iterator map_it;
            for(map_it = neighbor_counts.begin(); map_it != neighbor_counts.end(); map_it++){
                file << map_it->first << " " << map_it->second << endl;
            }
        }

    protected:
        string grid_file;
        string output;
        Stencil *stencil;
};

#endif
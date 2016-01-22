/**
Implementation of the NeighborhoodLifeRule ruletable.

(c) 2016 Tony Liu.
*/
#include "NeighborhoodLifeRule.h"

const string NeighborhoodLifeRule::NEIGHBORHOOD_ON = "Neighborhood";

void NeighborhoodLifeRule::initialize() {
    SimpleLifeRule::initialize();

    update_neighbor_counts();

    typename map<int,int>::iterator map_it;
    for(map_it = neighbor_counts.begin(); map_it != neighbor_counts.end(); map_it++){
        string n_label = NEIGHBORHOOD_ON + to_string(map_it->first);
        Property neighbor_count(n_label, map_it->second);

        metrics[n_label] = neighbor_count;
    }
}

void NeighborhoodLifeRule::compute_metrics() {
    SimpleLifeRule::compute_metrics();

    update_neighbor_counts();

    typename map<int,int>::iterator map_it;
    for(map_it = neighbor_counts.begin(); map_it != neighbor_counts.end(); map_it++){
        string n_label = NEIGHBORHOOD_ON + to_string(map_it->first);
        metrics[n_label].set_int(map_it->second);
    }
}

void NeighborhoodLifeRule::update_neighbor_counts() {
    neighbor_counts.clear();

    vector<string> labels = graph->get_vert_labels();
    vector<int> neighborhood_sizes;
    for(size_t i = 0; i < labels.size(); i++){
        int n_size = stencil->get_neighbors(labels[i])->size();

        if(neighbor_counts.count(n_size) == 0){
            neighbor_counts[n_size] = 0;
        }

        Property p = graph->get_data(labels[i])->get_property(GridGenerator::B_STATE);
        if(p.get_type() == Property::BOOL && p.b){
            neighbor_counts[n_size] += 1;
        }
    }
}

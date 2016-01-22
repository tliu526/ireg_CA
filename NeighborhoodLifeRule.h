/**
A derived LifeRule table for tracking neighborhood on frequency.

(c) 2016 Tony Liu
*/

#ifndef NEIGHBORHOODLIFERULE_H
#define NEIGHBORHOODLIFERULE_H

#include "SimpleLifeRule.h"

using namespace std;

class NeighborhoodLifeRule : public SimpleLifeRule {
    public:
        NeighborhoodLifeRule(Graph<std::string,Cell>* graph, Stencil* s, int init_percent, float seed = -1) :
        SimpleLifeRule(graph, s, init_percent, seed) {};

        void initialize();

        void compute_metrics();

    protected:
        //label for taking neighborhood counts
        static const string NEIGHBORHOOD_ON;

        //populates neighbor_counts 
        void update_neighbor_counts();
        
        map<int,int> neighbor_counts;
};

#endif
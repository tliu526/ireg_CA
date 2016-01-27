/**
A derived rule table class for investigating lambda values.

(c) 2016 Tony Liu.
*/

#ifndef LAMBDARULE_H
#define LAMBDARULE_H

#include "RuleTable.h"

#include <vector>

class LambdaRule : public RuleTable {
    public:   
        LambdaRule(Graph<std::string,Cell>* graph, Stencil* stencil, int num_neighbors, int num_states);

        virtual void transition();
        virtual void initialize();
        virtual void compute_metrics();

        virtual void apply_rule();
        size_t get_grid_state();

    protected:
        int num_neighbors;
        int num_states;
        int init_percent;

        /**
        holds the transition rules of the specified rule table. Without rotational invariants
        there needs to be 2^(N*log(K)) * log(K) bits, where N = num_neighbors and
        K = num_states.
        */
        std::vector<bool> bit_rule;
};

#endif
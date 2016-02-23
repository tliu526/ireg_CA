/**
Implements a variant of the GKL (Gacs-Kurdyumov-Levin) rule in two dimensional grids.
Algorithm dervied from me07.

If a cell's state is OFF, then it will take the majority of its C, N, and E inputs.
Otherwise, it will take the state of a majority of its C, S, W inputs.

This rule assumes a von Neumman neighborhood stencil (N=5).

(c) 2016 Tony Liu.
*/
#ifndef GKLRULE_H
#define GKLRULE_H

#include "MajorityRule.h"

class GKLRule : public MajorityRule {
    public:
        GKLRule(Graph<std::string,Cell>* graph, Stencil* s, int init_percent, float seed, int noise = 0);
    protected:
        void apply_rule(std::string& label);
};

#endif
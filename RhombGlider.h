/**
An implementation of the rule table presented in go12 that allows for gliders on penrose tilings.

(c) 2016 Tony Liu.
*/

#ifndef RHOMBGLIDER_H
#define RHOMBGLIDER_H

#include "LambdaRule.h"

class RhombGlider : public LambdaRule {
    public:      
        RhombGlider(Graph<std::string,Cell>* graph, Stencil* stencil, int seed, float s_radius = 0);

    protected:
        static const int NUM_NEIGHBORS;
        static const int NUM_STATES;

        void apply_rule(std::string &label);

        void init_transition_table();

};

#endif
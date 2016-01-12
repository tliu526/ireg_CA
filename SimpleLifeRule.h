/**
A direct implementation of Game of Life rules (2 or 3 neighbors). Extends RuleTable.

(c) 2016 Tony Liu.
*/

#ifndef SIMPLELIFERULE_H
#define SIMPLELIFERULE_H

#include "BinaryRuleTable.h"

class SimpleLifeRule : public BinaryRuleTable {
    public:
        SimpleLifeRule(Graph<std::string,Cell>* graph, float init_percent, float seed);  
        SimpleLifeRule(Graph<std::string,Cell>* graph, float init_percent, float seed, Stencil& s);  

        void transition();
        void initialize();
        void compute_metrics();
    protected:

        void apply_rule(std::string& label);
};

#endif

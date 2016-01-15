/**
A direct implementation of Game of Life rules (2 or 3 neighbors). Extends RuleTable.

GoL Rules:
- If a live cell has 2 or 3 living neighbors, then it remains alive
- Otherwise, a live cell with <2 or >3 neighbors will die
- Dead cells with exactly 3 living neighbors will be born

(c) 2016 Tony Liu.
*/

#ifndef SIMPLELIFERULE_H
#define SIMPLELIFERULE_H

#include "BinaryRuleTable.h"

class SimpleLifeRule : public BinaryRuleTable {
    public:
        SimpleLifeRule(Graph<std::string,Cell>* graph, Stencil* s, int init_percent, float seed = -1);

        void transition();
        void initialize();
        void compute_metrics();
    protected:

        void apply_rule(std::string& label);
};

#endif

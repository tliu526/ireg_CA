/**
A direct implementation of Game of Life rules (2 or 3 neighbors). Extends RuleTable.

(c) 2016 Tony Liu.
*/

#ifndef SIMPLELIFERULE_H
#define SIMPLELIFERULE_H

#include "RuleTable.h"

class SimpleLifeRule : public RuleTable {
    public:
        SimpleLifeRule(Graph<std::string,Cell>* graph, float init_percent, float seed);  
    protected:

};

#endif
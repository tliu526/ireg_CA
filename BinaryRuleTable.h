/**
A derived rule table class for only binary rules.

(c) 2016 Tony Liu.
*/

#ifndef BINARYRULETABLE_H
#define BINARYRULETABLE_H

#include "RuleTable.h"

class BinaryRuleTable : public RuleTable {
    public:
        BinaryRuleTable(Graph<std::string,Cell>* graph, float init_percent, float seed);

        /**
        Applies the transition rule to the entire graph.
        */
        virtual void transition();
        virtual void initialize();
        virtual void compute_metrics();

        size_t get_grid_state();

    protected:
        //metric names
        static const std::string PERCENT_ON;
        static const std::string INIT_PERCENT;

        /**
        Makes a single rule application.
        */
        virtual void apply_rule(std::string& label);

        /**
        Returns the total count of on cells
        */
        int get_on_count();
        
        //the initial percentage of ON  
        float init_percent_on;
};

#endif
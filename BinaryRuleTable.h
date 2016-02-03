/**
A derived rule table class for only binary rules.

(c) 2016 Tony Liu.
*/

#ifndef BINARYRULETABLE_H
#define BINARYRULETABLE_H

#include "RuleTable.h"

class BinaryRuleTable : public RuleTable {
    public:
        //if a seed is not provided (greater than 0), then the rule table will not initialize any state on the graph
        BinaryRuleTable(Graph<std::string,Cell>* graph, Stencil* stencil, int init_percent_on, float seed = -1, float radius = 0);

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
        static const std::string SUBREGION_ON;

        /**
        Makes a single rule application.
        */
        virtual void apply_rule(std::string& label);

        /**
        Returns the total count of on cells
        */
        int get_on_count();

        /**
        Returns the count of neighboring on cells to cell s
        */
        int get_on_count(std::string& s);
        
        /**
        Returns the count of on cells in the vector
        */
        int get_on_count(std::vector<std::string>& v);
        


        //the initial percentage of ON  
        float init_percent_on;
        int   init_percent_int;
        float init_radius;

        //for keeping track of the subregion labels
        std::vector<string> subregion_labels;
};

#endif

/**
A derived class that holds all metrics needed for majority computation.

(c) 2016 Tony Liu.
*/

#ifndef MAJORITYRULE_H
#define MAJORITYRULE_H

#include "BinaryRuleTable.h"

class MajorityRule : public BinaryRuleTable {
    public: 
        MajorityRule(Graph<std::string,Cell>* graph, Stencil* s,int init_percent, float seed);
    
        /**
        Applies the transition rule to the entire graph.
        */
        void transition();
        void initialize();
        void compute_metrics();

    protected:
        //metric names
        static const std::string CORRECT_CLASS;

        /**
        Makes a single rule application.
        */
        virtual void apply_rule(std::string& label);

        //the target classification: true is majority ON, false is majority OFF 
        bool target_class;
};


#endif
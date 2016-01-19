/**
A derived rule table class for investigating lambda values.

(c) 2016 Tony Liu.
*/

#ifndef LAMBDARULE_H
#define LAMBDARULE_H

#include "RuleTable.h"

class LambdaRule : public RuleTable {
    public:   
        void transition();
        void initialize();
        void compute_metrics();

        size_t get_grid_state();

    protected:
        void apply_rule();
};

#endif
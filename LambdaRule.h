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
  LambdaRule(Graph<std::string,Cell>* graph, Stencil* stencil, int num_neighbors, int num_states, int seed = -1);

        virtual void transition();
        virtual void initialize();
        virtual void compute_metrics();

        /**
        Creates a rule table with lambda level of l. Corresponds to Langton's "random table"
        method.
        */
        void set_lambda(int l);

        /**
        Increments the lamda value, updates the rule table, and returns the new lambda level.
        Corresponds to Langton's "table walk-through" method.
        */
        int increment_lambda();

        size_t get_grid_state();

    protected:
        //metric names 
        static const std::string LAMBDA; //lambda value for a particular configuration
        static const std::string FREQUENCY; //Frequency of state appearances


        virtual void apply_rule(std::string &label);

        /*
        Converts the cell neighborhood to an index of bit_rule. Currently assumes that 
        the neighborhood is correctly ordered in the neighborhood maps provided by stencil.
        */
        int get_bit_rule_index(std::string &label);

        /**
        Returns the state at index as specified by bit_rule.
        */
        int get_bit_rule_state(int index);

        int q_state; //the quiescent state
        int lambda; //the current value for lamda, integer from 1 to 100 for ease of indexing

        int num_neighbors;
        int num_states;
        int init_percent;
        int seed;

        //the number of bits to represent a single state
        int num_bits;
        /**
        holds the transition rules of the specified rule table. Without rotational invariants
        there needs to be 2^(N*log(K)) * log(K) bits, where N = num_neighbors and
        K = num_states.
        */
        std::vector<bool> bit_rule;
};

#endif

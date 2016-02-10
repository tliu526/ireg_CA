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
  LambdaRule(Graph<std::string,Cell>* graph, Stencil* stencil, int num_neighbors, int num_states, int seed);

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

        /**
        Initializes the transition table with the lexographically minimal strings
        */
        void init_transition_table();

        /**
        Returns the lexicographically minimal string rotation for in
        TODO need to implement faster rotation
        */
        std::string min_rotation(std::string& in);

        /**
        Returns the correctly formatted min rotation key for trans table.
        */
        std::string get_trans_key(std::string& label);

        /*
        Converts the cell neighborhood to an index of bit_rule. Currently assumes that 
        the neighborhood is correctly ordered in the neighborhood maps provided by stencil.
        */
        int get_bit_rule_index(std::string &label);

        /**
        Returns the state at index as specified by bit_rule.
        */
        int get_bit_rule_state(int index);

        /**
        Sets the state in the bit rule table at the specified index.
        */
        void set_bit_rule_state(int index, int state);

        /**
        Computes the frequency metrics to be stored
        */
        void compute_freq();

        int q_state; //the quiescent state
        string q_str; //the quiescent neighborhood
        int lambda; //the current value for lamda, integer from 1 to 100 for ease of indexing
        int nonq_count; //tracks the number of states not mapped to the quiescent state

        int num_neighbors;
        int num_states;
        int init_percent;
        int seed;

        std::map<int,int> state_counts; //for tracking frequencies
        std::map<std::string, int> trans_table; //transition table, min rotation string as key

        std::vector<string> trans_keys; //vector of transition keys to modify
        std::vector<string>::iterator key_it; //an iterator for trans_keys
        default_random_engine gen;        
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

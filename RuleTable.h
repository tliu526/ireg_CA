/*
A base class for transition rules. This will take a Cell as well as a Graph and 
transition it to the next specified state.

A data structure for storing all transition rules for non-Euclidean rule tables. The idea is 
to hold a byte array for each possible number of neighbors, with the byte array corresponding to
the same representation as 1D CA rule representations (like rule 110).

Or, if we only care about counts of number of neighbors being on or off, we have an bit array with
length equal to the total number of neighbors.

Things to think about:
- state history (separate checksum class?)
- need a way to store rule tables to be mutated/iterated through (ala lambda)
- Consistent directionality of rule application

Currently, RuleTable looks for the keyword property "State" in order for it to make 
rule transitions.

(c) 2015 Tony Liu.
*/

#ifndef RULETABLE_H
#define RULETABLE_H

#include "Cell.h"
#include "Graph.h"
#include "Stencil.h"
#include "Property.h"
#include "GridGenerator.h"

#include <string>
#include <vector>
#include <map>
#include <bitset>

class RuleTable {
	public:
		RuleTable() {};
		RuleTable(Graph<std::string, Cell> *graph, Stencil* s);

		/**
		Transitions the entire grid to the next timestep. Calls apply_rule and update_graph.
		*/
		virtual void transition();
		
		/**
		Initializes the RuleTable. All hard computation
		should go here.
		*/
		virtual void initialize();

		/**
		Computes the relevant metrics for the Rule Table.
		*/
		virtual void compute_metrics();

		/**
		Gives the current state of the grid into a bitvec and returns a bitvec hash. 
		TODO MD5 hash
		*/
		virtual size_t get_grid_state();

		/**
		Returns a pointer to the metrics map
		*/
		std::map<std::string, Property>* get_metrics();

	protected:
		/**
		Computes the next state and stores it in state_map
		*/
		virtual void apply_rule(std::string& label);

		/**
		Writes all the new states to the graph. 
		*/
		virtual void update_graph();

		//The rule type, must match with Stencil type
		RuleType type;
		//The mapping between the rule table and irregular neighborhoods
		Stencil* stencil;
		//pointer to the graph to be updated
        Graph<std::string, Cell>* graph;

        //vector of labels that need to be checked for possible updates
        //For spreading activation implementation of rule table
        std::vector<std::string> cells_to_update;

        //map containing all the states that need to be updated
        std::map<std::string, Property> state_map;
		
		//A map of all relevant metrics
        std::map<std::string, Property> metrics;

		//determines size of neighborhood
		float radius;

		int num_cells;

		//seed for RNG
		float seed;

		//TODO keeps track of the checksums for previous states
		//std::vector<long> state_history; 
};

#endif
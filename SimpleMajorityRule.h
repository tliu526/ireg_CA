/*
A simple rule table that switches the target cell into the majority state of its surrounding
neighbors.

(c) 2016 Tony Liu.
*/

#ifndef SIMPLEMAJORITYRULE_H
#define SIMPLEMAJORITYRULE_H

#include "RuleTable.h"

#include <string>
#include <list>
#include <bitset> 

class SimpleMajorityRule : public RuleTable {
	public: 
		SimpleMajorityRule(Graph<std::string,Cell>* graph, float init_percent, float seed);
	
		/**
		Applies the transition rule to the entire graph.
		*/
		void transition();
		void initialize();
		void compute_metrics();

		std::bitset get_grid_state();

	protected:
		//metric names
		static const std::string CORRECT_CLASS;
		static const std::string PERCENT_ON;

		/**
		Makes a single rule application.
		*/
		void apply_rule(std::string& label);

		/**
		Returns the total count of on cells
		*/
		int get_on_count();

		//the target classification: true is majority ON, false is majority OFF 
		bool target_class;
		//the initial percentage of ON  
		float init_percent_on;
		//seed for RNG
		float seed;
};

#endif
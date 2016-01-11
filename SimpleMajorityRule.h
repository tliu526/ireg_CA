/*
A simple rule table that switches the target cell into the majority state of its surrounding
neighbors.

(c) 2016 Tony Liu.
*/

#ifndef SIMPLEMAJORITYRULE_H
#define SIMPLEMAJORITYRULE_H

#include "BinaryRuleTable.h"

#include <string>
#include <list>

class SimpleMajorityRule : public BinaryRuleTable {
	public: 
		SimpleMajorityRule(Graph<std::string,Cell>* graph, float init_percent, float seed);
	
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
		void apply_rule(std::string& label);

		//the target classification: true is majority ON, false is majority OFF 
		bool target_class;
};

#endif
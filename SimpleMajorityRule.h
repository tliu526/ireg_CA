/*
A simple rule table that switches the target cell into the majority state of its surrounding
neighbors. Currently pseudocode.

(c) 2016 Tony Liu.
*/

#ifndef SIMPLEMAJORITYRULE_H
#define SIMPLEMAJORITYRULE_H

#include "RuleTable.h"

#include <string>
#include <list>

class SimpleMajorityRule : public RuleTable {
	public: 
		SimpleMajorityRule();
	
		/**
		Applies the transition rule to the entire graph.
		*/
		void transition(Graph<std::string,Cell>* graph);

	protected:
		/**
		Makes a single rule application.
		*/
		void apply_rule(std::string label, Graph<std::string,Cell>* graph);
};

#endif
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

class SimpleMajorityRule : public RuleTable {
	public: 
		SimpleMajorityRule(Graph<std::string,Cell>* graph);
	
		/**
		Applies the transition rule to the entire graph.
		*/
		void transition();

	protected:
		/**
		Makes a single rule application.
		*/
		void apply_rule(std::string& label);
};

#endif
/*
A simple rule table that switches the target cell into the majority state of its surrounding
neighbors.

(c) 2016 Tony Liu.
*/

#ifndef SIMPLEMAJORITYRULE_H
#define SIMPLEMAJORITYRULE_H

#include "MajorityRule.h"

#include <string>
#include <list>

class SimpleMajorityRule : public MajorityRule {
	public: 
		SimpleMajorityRule(Graph<std::string,Cell>* graph, Stencil* s,int init_percent, float seed, int noise = 0);

	protected:
		/**
		Makes a single rule application.
		*/
		void apply_rule(std::string& label);
};

#endif
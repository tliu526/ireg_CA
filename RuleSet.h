/*
An abstract class for transition rules. This will take a Cell as well as a Graph and transition it to the next
specified state.
*/

#ifndef RULESET_H
#define RULESET_H

#include "Cell.h"
#include "Graph.h"

#include <string>

class RuleSet {
	public:
		void transition(std::string label, Graph<std::string,Cell> graph) = 0;
};

#endif
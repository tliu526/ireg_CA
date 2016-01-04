/*
An abstract class for transition rules. This will take a Cell as well as a Graph and 
transition it to the next specified state.

Things to think about:
- state history (separate checksum class?)
- need a way to store rule tables to be mutated/iterated through (ala lambda)


(c) 2015 Tony Liu.
*/

#ifndef RULETABLE_H
#define RULETABLE_H

#include "Cell.h"
#include "Graph.h"

#include <string>
#include <vector>

typedef enum RuleType = { 
	EUCLIDEAN, 
	MOORE, 
	VON_NEUMANN
} RuleType;

class RuleTable {
	public:
		void transition(Graph<std::string,Cell> graph) = 0;

	protected:
		RuleType rule_type;
		float radius; //determines size of neighborhood
		//keeps track of the checksums for previous states, TODO checksum class?
		std::vector<long> state_history; 

		void apply_rule(std::string label) = 0;
};

#endif
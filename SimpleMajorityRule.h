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
		void transition(Graph<std::string,Cell>& graph){
			//write current state to state_history

			//iterate over all cells in a consistent order, calling apply_rule on each cell
			//for all cells (label):
			//	apply_rule(label)

		}

	protected:
		void apply_rule(std::string label, Graph<std::string,Cell>& graph){

			std::list<Cell>* neighbors = graph.get_neighbors(label);

			//for all neighbors:
			//check state of the neighbors in state_history
			//set state of current cell
		}
};

#endif
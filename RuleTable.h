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
(c) 2015 Tony Liu.
*/

#ifndef RULETABLE_H
#define RULETABLE_H

#include "Cell.h"
#include "Graph.h"
#include "Stencil.h"

#include <string>
#include <vector>


class RuleTable {
	public:
		RuleTable() {};
		RuleTable(Stencil& s);

		/**
		Transitions the entire grid to the next timestep.
		*/
		virtual void transition(Graph<std::string,Cell>* graph);
		
		virtual void initialize();

	protected:
		RuleType type;
		Stencil stencil;

		float radius; //determines size of neighborhood
		//keeps track of the checksums for previous states, TODO checksum class?
		std::vector<long> state_history; 

		virtual void apply_rule(std::string label, Graph<std::string,Cell>* graph);
};

#endif
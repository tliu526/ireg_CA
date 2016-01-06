/*
A base class that maps regular neighborhoods as described by a rule table to irregular
neighborhoods.

Things to think about:
- how precisely should we control the mappings? (Possible solution: just have slight
  variations on different Stencil implementations)

(c) 2016 Tony Liu.
*/

#ifndef STENCIL_H
#define STENCIL_H

#include "Cell.h"
#include "Graph.h"

#include <map>
#include <vector>
#include <string>
#include <list>

//Enumeration holds the rule type
typedef enum RuleType { 
    EUCLIDEAN, 
    MOORE, 
    VON_NEUMANN,
    OTHER
} RuleType;

class Stencil {
    public:
        Stencil();
        //Stencil(Graph<std::string, Cell>* g);
        /**
        Initialize the neighborhood map
        */
        virtual void initialize(Graph<std::string, Cell>* g);

        /**
        Returns the neighbor list as specified by the stencil.
        */
        std::vector<std::string>* get_neighbors(std::string& label);
    protected:
        RuleType type;
        Graph <std::string, Cell>* graph;
        std::map<std::string, std::vector<std::string>> neighbor_map;
};

#endif
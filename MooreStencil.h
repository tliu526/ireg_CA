/**
A stencil that provides a consistent mapping of four neighbors to a Moore orientation.
The neighbors of a cell will always be presented as NESW (clockwise from north).

TODO mapping neighborhoods of >4 to a Moore neighborhood.

(c) 2016 Tony Liu.
*/

#ifndef MOORESTENCIL_H
#define MOORESTENCIL_H

#include "Stencil.h"
#include "GridGenerator.h"

#include <string>

class MooreStencil : public Stencil {
    public: 
        MooreStencil(Graph<std::string, Cell>* graph, GridGenerator* gen);

        void initialize();

    protected:
        GridGenerator* generator;
};

#endif
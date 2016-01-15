/**
A stencil that includes both edges and vertices in a cell's neighborhood.

(c) 2016 Tony Liu.
*/

#ifndef VERTSTENCIL_H
#define VERTSTENCIL_H

#include "Stencil.h"

class VertStencil : public Stencil {
    public:
        VertStencil(Graph<std::string, Cell>* graph, GridGenerator* generator
};

#endif
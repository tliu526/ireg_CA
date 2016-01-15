/**
A stencil that includes cells that share either an edge or vertex in a neighborhood.

(c) 2016 Tony Liu.
*/

#ifndef VERTSTENCIL_H
#define VERTSTENCIL_H

#include "Stencil.h"
#include "GridGenerator.h"

#include <string>

class VertStencil : public Stencil {
    public:
        VertStencil(Graph<std::string, Cell>* graph, GridGenerator* generator);

        void initialize();

    protected:
        GridGenerator* generator;
};

#endif
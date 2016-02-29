/**
A regular grid generator, used for control and reproduction of results found in papers.
Currently defaults to a von Neumann neighborhood.

TODO:
- generalize to other neighborhoods

(c) 2016 Tony Liu.
*/

#ifndef REGULARGRIDGENERATOR_H
#define REGULARGRIDGENERATOR_H

#include "GridGenerator.h"

#include <vector>

class RegularGridGenerator : public GridGenerator {
public:
    //TODO add seed
    RegularGridGenerator(int min_x, int max_x, int min_y, int max_y, bool toroidal = false, int degen = 0);

    void generate_graph();

protected:
    bool is_toroidal; // whether or not the boundaries wrap around
    int degeneracy; // the amount of degeneracy applied to the grid

    static const float OFFSET;
    /**
    Initializes all Points, Edges, Faces
    */
    void init_grid();

    /**
    Degenerates the grid 
    */
    int degenerate_grid();

    /**
    Returns the corresponding poly for a generator point.
    */
    Poly construct_square(Point& gen_pt);
    std::vector<Edge> gen_edges; //for initializing graph in generate_graph()
};

#endif
/*
A GridGenerator that generates a quad diagram based off the voronoi quad technique. 
Can read in the data file of any grid and generate the diagram.

(c) 2016 Tony Liu.
*/

#ifndef VQUADGRIDGENERATOR_H
#define VQUADGRIDGENERATOR_H

#include "GridGenerator.h"

#include <string>
#include <map>

class VQuadGridGenerator : public GridGenerator {
    public:
        VQuadGridGenerator(std::string file, int degen_pct = 0, int s = 0);

        void generate_graph();

    private:
        //the percentage of generator points to be removed
        int degen_percent;
        //seed for randomly selecting points
        int seed;

        void init_vgrid();

        Poly build_quad(string& e_label, string& gp_1, string& gp_2);
        //for keeping track of which edges are associated with which gen_pts
        std::map<std::string, std::vector<std::string>> edge_gen_pt_map;

        /**
        Removes generator points from gen_pt_face_map according to degen_percent.
        Returns the number of pts removed.
        */
        int degenerate_grid();
};

#endif

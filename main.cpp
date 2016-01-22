/**
Where all experiments are called and ran.

TODO scripting capability through input files or command line args.

(c) 2016 Tony Liu.
*/

#include "PenroseLifeVert22.h"
#include "RegularGridGenerator.h"
#include "PenroseAsh.h"
#include "PenroseSingle.h"
#include "ConnectivityExpr.h"

#include <string>

using namespace std;

int main(int argc, char *argv[]){

/*
    GridGenerator gen("crhx.txt");
    VertStencil stencil(gen.get_graph(), &gen);
    SimpleLifeRule rule(gen.get_graph(), &stencil, 100, 2, 38);
    rule.initialize();
    gen.grid_to_dot("big_soup_test");
*/
    PenroseAsh expr("crhx.txt", "crhx", 100, 1000, 38);
    //PenroseSingle expr("crhx.txt", "crhx_9", 9, 1, 1000, 38);
    expr.run();
    return 0;
}
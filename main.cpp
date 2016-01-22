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

    GridGenerator gen("crh.txt");
    VertStencil stencil(gen.get_graph(), &gen);
    SimpleLifeRule rule(gen.get_graph(), &stencil, 100, 2, 60);
    rule.initialize();
    gen.grid_to_dot("soup_test");
//    PenroseSingle expr("crh.txt", "crh_26_nbd", 26, 100, 1000);
//    expr.run();
    return 0;
}
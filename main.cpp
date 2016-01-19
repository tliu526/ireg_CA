/**
Where all experiments are called and ran.

TODO scripting capability through input files or command line args.

(c) 2016 Tony Liu.
*/

#include "PenroseLifeVert22.h"
#include "RegularGridGenerator.h"
#include "MooreStencil.h"

#include <string>

using namespace std;

int main(int argc, char *argv[]){
//    PenroseLifeVert22 expr;
//  expr.run();

    RegularGridGenerator gen(0, 64, 0, 64, true);
    MooreStencil(gen.get_graph(), &gen);

    return 0;

}
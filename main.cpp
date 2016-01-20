/**
Where all experiments are called and ran.

TODO scripting capability through input files or command line args.

(c) 2016 Tony Liu.
*/

#include "PenroseLifeVert22.h"
#include "RegularGridGenerator.h"
#include "PenroseAsh.h"
#include "PenroseSingle.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]){
    PenroseSingle expr("crh.txt", "crh_long_59", 59, 19, 1000);
    expr.run();

    return 0;
}
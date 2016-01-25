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

#include <unistd.h>
#include <string>

using namespace std;

typedef enum Expmt {
    LIFE = 1,
	L_MAJORITY = 2 //local majority
} Expmt;


/** Experiment parameters **/
string infile;
string outname;
int max_time;
int num_configs;
int subregion_rad;

/** Single Run Experiment parameters **/


/**
Prints the help listing for this program.
*/
void help() {
    cout << "Usage: ca -i infile -o outname -e experiment [-t time] [-c configs] [-s subregion \%]" << endl;
	cout << "\t-i\tThe input graph file" << endl;
	cout << "\t-o\tThe output metrics/dot name" << endl;
	cout << "\t-e\tThe experiment type" << endl; //TODO
	cout << "\t-t\tMaximum number of timesteps" << endl;
	cout << "\t-c\tNumber of different starting configurations (trials) per percentage" << endl;
	cout << "\t-s\tSize of subregion for initial configuration" << endl;
	cout << "Example: " << endl; //TODO
	
}

/**
Parses arguments using getopt and sets appropriate variables to run.
*/
void parse_args(int argc, char **argv) {
    int c; 

    while((c = getopt(argc, argv, "i:o:e:t:c:")) != -1) {
  	    switch (c) {
		case 'i':
		    infile = string(optarg);
			break;
		case 'o':
            outname = string(optarg);
			break;
	    case 't':
		    max_time = atoi(optarg);
			break;
	    case 'c':
		    num_configs = atoi(optarg);
			break;
	    case '?':
		    //TODO
	    default:
		    help();

		}
    }

}

/**
Initializes experiments and runs them.
*/
void run() {

}

int main(int argc, char **argv){

/*
    GridGenerator gen("crhx.txt");
    VertStencil stencil(gen.get_graph(), &gen);
    SimpleLifeRule rule(gen.get_graph(), &stencil, 100, 2, 38);
    rule.initialize();
    gen.grid_to_dot("big_soup_test");
*/
    PenroseAsh expr("ckdx.txt", "ckdx", 100, 1000, 38);
    //PenroseSingle expr("crhx.txt", "crhx_9", 9, 1, 1000, 38);
    expr.run();
    return 0;
}

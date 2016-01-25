/**
Where all experiments are called and ran.

Things TODO
- Stencil options from command line
- GridGenerator options from command line (currently only reads in graph files)

(c) 2016 Tony Liu.
*/

#include "PenroseLifeVert22.h"
#include "RegularGridGenerator.h"
#include "PenroseAsh.h"
#include "LifeSingle.h"
#include "ConnectivityExpr.h"

#include <unistd.h>
#include <string>

using namespace std;

typedef enum Expmt {
    S_LIFE = 1, //simple Life
	L_MAJORITY = 2 //local majority
} Expmt;


/** Experiment parameters **/
string infile;
string outname;
Expmt expmt_type;
int max_time;
int num_configs;
int subregion_rad = 0; //optional

/** Single Run Experiment parameters **/
bool single_expmt = false;
int init_percent;
int seed;

/**
Prints out the experiment types and options.
*/
void print_experiment_opt(){
    cout << "Full experiments need -t -c set" << endl;
    cout << "Single experiments (-S) need -t -c -p -s set" << endl;
    cout << "The following are valid experiments:" << endl;
    cout << "\tgol\tGame of Life (simple)" << endl;
    cout << "\tlm\tLocal Majority" << endl;
}

/**
Prints the help listing for this program.
*/
void help() {
    cout << "Usage: ca -i infile -o outname -e experiment [-S] [-t time]" << endl; 
    cout << "[-c configs] [-p ON percentage] [-r subregion \%]" << endl;
    cout << "[-s seed]" << endl;
	cout << "\t-i\tThe input graph file" << endl;
	cout << "\t-o\tThe output metrics/dot name" << endl;
	cout << "\t-e\tThe experiment type" << endl; //TODO
    cout << "\t-S\tSpecifies a single run experiment" << endl;
	cout << "\t-t\tMaximum number of timesteps" << endl;
	cout << "\t-c\tNumber of different starting configurations (trials)" << endl;
    cout << "\t-p\tInitial ON percentage for single runs" << endl;
    cout << "\t-r\tSize of subregion for initial configuration" << endl;
    cout << "\t-s\tA particular seed for the RNG" << endl;
	cout << "Example: " << endl; //TODO
    print_experiment_opt();
	exit(1);
}
/**
Parses arg to set appropriate experiment type.
//TODO add flag checking for correct parameters
*/
void set_experiment(string arg){

    if(arg == "gol")     expmt_type = S_LIFE;
    else if(arg == "lm") expmt_type = L_MAJORITY;
    
    else {
        print_experiment_opt();
        exit(1);
    }
}

/**
Parses arguments using getopt and sets appropriate variables to run.
*/
void parse_args(int argc, char **argv) {
    int c; 

    if(argc < 2) help();

    while((c = getopt(argc, argv, "i:o:e:t:c:p:Ss:h")) != -1) {
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
            case 'e':
                set_experiment(string(optarg));
                break;
            case 'p':
                init_percent = atoi(optarg);
                break;
            case 's':
                seed = atoi(optarg);
                break;
            case 'S':
                single_expmt = true;
                break;
            case '?':
		        //TODO
            case 'h':
            default:
                help();
		}
    }

}

/**
Initializes experiments and runs them.
*/
void run() {
    switch(expmt_type){
        case S_LIFE:
            if(single_expmt) { //TODO flag checks
                LifeSingle expmt(infile, outname, init_percent, seed, max_time, subregion_rad);
                expmt.run();
            } 
            else if (!single_expmt /*TODO flag checks*/) {
                cout << "Running penroseAsh" << endl;
                PenroseAsh expmt(infile, outname, num_configs, max_time, subregion_rad);
                expmt.run();
            }
            break;
    }    
}

int main(int argc, char **argv){
    parse_args(argc, argv);
    run();
/*
    GridGenerator gen("crhx.txt");
    VertStencil stencil(gen.get_graph(), &gen);
    SimpleLifeRule rule(gen.get_graph(), &stencil, 100, 2, 38);
    rule.initialize();
    gen.grid_to_dot("big_soup_test");
*/
    /*
    PenroseAsh expr("ckdx.txt", "ckdx", 100, 1000, 38);
    //PenroseSingle expr("crhx.txt", "crhx_9", 9, 1, 1000, 38);
    expr.run();
    */
    return 0;
}

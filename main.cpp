/**
Where all experiments are called and ran.

Things TODO
- Stencil options from command line
- GridGenerator options from command line -g flag (currently only reads in graph files) 

(c) 2016 Tony Liu.
*/

#include "RegularGridGenerator.h"
#include "LifeAsh.h"
#include "LifeSingle.h"
#include "LambdaExpr.h"
#include "ConnectivityExpr.h"
#include "LocalMajority.h"
#include "GKLMajority.h"
#include "FFLocalMajority.h"

#include <unistd.h>
#include <string>

using namespace std;

typedef enum Expmt {
    S_LIFE = 1, //simple Life
    L_MAJORITY = 2, //local majority
    LAMBDA = 3, //lambda experiments
    GKL_MAJ = 4 //gkl majority experiments
} Expmt;

typedef enum ArgFlag {
    IN = 1,
    OUT = 2,
    EXPMT = 4,
    TIME = 8,
    CONFIGS = 16,
    PERCENT = 32,
    SEED = 64,
    SINGLE = 128,
    NBR_METRICS = 256,
    NOISE = 512,
    FIFTY = 1024,
    STATES = 2048
} ArgFlag;

/** Experiment types **/
const string LAMBDA_STR = "lambda";
const string GOL_STR = "gol";
const string LM_STR = "lm";
const string GKL_STR = "gkl";

/** Experiment parameters **/
string infile;
string outname;
Expmt expmt_type;
int max_time;
int num_configs;
int subregion_rad = 0; //optional
int flags = 0;

/** Majority parameters **/
int noise = 0;

/** Single Run Experiment parameters **/
int init_percent;
int seed;

/** Lambda parameters **/
int num_states;

/** Experiment check flags **/
int FULL_EXPMT = (IN | OUT | EXPMT | TIME | CONFIGS);
int SINGLE_EXPMT = (IN | OUT | EXPMT | TIME | SEED | PERCENT | SINGLE);

int LAMBDA_EXPMT = (IN | OUT | EXPMT | TIME | CONFIGS | SEED);

/**
Prints out the experiment types and options.
*/
void print_experiment_opt(){
    cout << "EXPERIMENTS" << endl;
    cout << "\tgol\tGame of Life (simple)" << endl;
    cout << "\tlm\tLocal Majority" << endl;
    cout << "\tlambda\tLambda" << endl;
    cout << "\tgkl\tGKL Majority" << endl;
    cout << endl;
    cout << "\tFull experiments need -t -c set" << endl;
    cout << "\tSingle experiments (-S) need -t -p -s set" << endl;
    cout << "\tLambda experiments need -i OR -g and -t -c -s set" << endl;
}

/**
Prints the help listing for this program.
*/
void help() {
    cout << "USAGE" << endl;
    cout << "\t-i infile -o outname -e experiment [-SNF] [-t time]" << endl; 
    cout << "\t[-c configs] [-p ON percentage] [-r subregion \%]" << endl;
    cout << "\t[-s seed] [-g graph_type] [-n noise] [-k states]" << endl;
    cout << endl;
    cout << "DETAILS" << endl;
	cout << "\t-i\tThe input graph file" << endl;
	cout << "\t-o\tThe output metrics/dot name" << endl;
	cout << "\t-e\tThe experiment type" << endl; //TODO
    cout << "\t-S\tSpecifies a single run experiment" << endl;
    cout << "\t-N\tRecords additional metrics about neighborhood frequency" << endl;
	cout << "\t-t\tMaximum number of timesteps" << endl;
	cout << "\t-c\tNumber of starting configurations/trials" << endl;
    cout << "\t-p\tInitial ON percentage for single runs" << endl;
    cout << "\t-r\tSize of subregion for initial configuration" << endl;
    cout << "\t-s\tA particular seed for the RNG (single runs)" << endl;
    cout << "\t-g\tSpecifies a graph type to generate TODO" << endl;
    cout << "\t-n\tSpecifies amount of temporal noise for majority exprs" << endl;
    cout << "\t-F\tSpecifies a fifty-fifty experiment for majority exprs" << endl;
    cout << "\t-k\tSpecifies number of states for a lambda experiment" << endl;
	cout << endl;
    print_experiment_opt();
	exit(1);
}
/**
Parses arg to set appropriate experiment type.
//TODO add flag checking for correct parameters
*/
void set_experiment(string arg){

    if(arg == GOL_STR)     expmt_type = S_LIFE;
    else if(arg == LM_STR) expmt_type = L_MAJORITY;
    else if(arg == LAMBDA_STR) expmt_type = LAMBDA;
    else if(arg == GKL_STR) expmt_type = GKL_MAJ;
    
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

    while((c = getopt(argc, argv, "SNFhi:o:e:t:c:p:s:r:n:k:")) != -1) {
  	    switch (c) {
            case 'i':
                infile = string(optarg);
                flags |= IN;
                break;
            case 'o':
                outname = string(optarg);
                flags |= OUT;
                break;
            case 't':
                max_time = atoi(optarg);
                flags |= TIME;
                break;
            case 'c':
                num_configs = atoi(optarg);
                flags |= CONFIGS;
                break;
            case 'e':
                set_experiment(string(optarg));
                flags |= EXPMT;
                break;
            case 'p':
                init_percent = atoi(optarg);
                flags |= PERCENT;
                break;
            case 's':
                seed = atoi(optarg);
                flags |= SEED;
                break;
            case 'r':
                subregion_rad = atoi(optarg);
                cout << "subregion: " << subregion_rad << endl;
                //TODO flags?
                break;
            case 'S':
                flags |= SINGLE;
                break;
            case 'N':
                flags |= NBR_METRICS;
                break;
            case 'n':
                flags |= NOISE;
                noise = atoi(optarg);
                break;
            case 'F':
                flags |= FIFTY;
                break;
            case 'k':
                flags |= STATES;
                num_states = atoi(optarg);
                break;
            case '?':
                if(optopt == 'i') cout << "An input file is required" << endl;
                else if(optopt == 'o') cout << "An output name is required" << endl;
                else if(optopt == 't') cout << "A max time is required" << endl;
                break;
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
            if((flags & SINGLE_EXPMT) == SINGLE_EXPMT) { //TODO flag checks
                //TODO neighborhood flag
                cout << "Running LifeSingle" << endl;
                bool nbr_metrics = flags & NBR_METRICS;
                LifeSingle expmt(infile, outname, init_percent, seed, max_time, subregion_rad, nbr_metrics);
                expmt.run();
            } 
            else if ((flags & FULL_EXPMT) == FULL_EXPMT) {
                cout << "Running LifeAsh" << endl;
                LifeAsh expmt(infile, outname, num_configs, max_time, subregion_rad);
                expmt.run();
            }
            else {
                print_experiment_opt();
                exit(1);
            }
            break;

        case L_MAJORITY:
            if((flags & SINGLE_EXPMT) == SINGLE_EXPMT) { //TODO flag checks
                cout << "Running LMSingle TODO" << endl;
                //LifeSingle expmt(infile, outname, init_percent, seed, max_time, subregion_rad);
                //expmt.run();
            } 
            else if ((flags & FULL_EXPMT) == FULL_EXPMT) {
                if(flags & FIFTY){
                    cout << "Running FFLocalMajority" << endl;
                    FFLocalMajority expmt(infile, outname, num_configs, max_time, noise);
                    expmt.run();
                }
                else{
                    cout << "Running LocalMajority" << endl;
                    LocalMajority expmt(infile, outname, num_configs, max_time, noise);
                    expmt.run();
                }
            }
            else {
                print_experiment_opt();
                exit(1);
            }
            break;

        case LAMBDA:
            if((flags & LAMBDA_EXPMT) == LAMBDA_EXPMT) {
                if((flags & STATES) == STATES){
                    cout << "Running Lambda Expr" << endl;
                    cout << "Number of States: " << num_states << endl;
                    LambdaExpr expmt(infile, outname, num_configs, max_time, seed, subregion_rad, num_states);
                    expmt.run();                    
                }
                else {
                    cout << "Running Lambda Expr" << endl;
                    LambdaExpr expmt(infile, outname, num_configs, max_time, seed, subregion_rad);
                    expmt.run();
                }}
            else {
                print_experiment_opt();
                exit(1);
            }

        case GKL_MAJ:
            if((flags & SINGLE_EXPMT) == SINGLE_EXPMT) { //TODO flag checks
                cout << "Running GKL Single TODO" << endl;
                //LifeSingle expmt(infile, outname, init_percent, seed, max_time, subregion_rad);
                //expmt.run();
            } 
            else if ((flags & FULL_EXPMT) == FULL_EXPMT) {
                cout << "Running GKL Majority" << endl;
                GKLMajority expmt(infile, outname, num_configs, max_time);
                expmt.run();
            }
            else {
                print_experiment_opt();
                exit(1);
            }

        default:
            print_experiment_opt();
            exit(1);

    }    
}

int main(int argc, char **argv){
    parse_args(argc, argv);
    run();
    return 0;
}

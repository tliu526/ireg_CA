/*
Simulates the computation. Holds a grid generator for reading and writing to file.

Things to think about:
- Scripting capability

(c) 2015 Tony Liu.
*/

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "GridGenerator.h"
#include "RuleTable.h"

#include <queue>
#include <map>
#include <string>

class Simulator {
    public:
        typedef enum Event {
            UPDATE_GRAPH = 1, //increments the simulation by one timestep
            CALC_METRICS = 2, //updates all available metrics 
            STOP_SIMULATION = 4, //stops the simulation and pushes flags for writing to file
            UPDATE_DISPLAY = 8, //updates the display, TODO
            STATS_TO_FILE = 16, //writes metrics to given file
            GRID_SNAPSHOT = 32, //generates a neato graphviz snapshot of grid state
        } Event;

        //TODO a struct of options to pass
        Simulator(GridGenerator* g, RuleTable* r, int max, std::string file, int snapshot = 0);
        Simulator() {};

        /**
        Runs the simulation until the event queue is either empty or terminated
        */
        void simulate();

        /**
        Writes state statistics as well as other calculations to file.

        @param file filename written to.
        */
        void stats_to_file(std::string file);

        /**
        Writes state statistics as well as other calculations to file. Uses stat_file as
        output file.
        */
        void stats_to_file();

        /**
        Writes the metric headers to the output file
        */
        void metric_headers();

    protected:
        static const std::string STATS_EXTENSION; //Metrics file extension
        static const std::string STATS_DELIM; //Metrics delimiter

        /*** Simulator State Variables***/
        static const std::string TIME;
        static const std::string PERIOD;

        GridGenerator* generator;
        Graph<std::string, Cell>* grid;
        RuleTable* rule_table;

        std::queue<Event> event_queue;

        //whether or not the simulation is running
        bool running;
        //output file name
        std::string out_file;
        //how often to take a snapshot
        int snapshot_freq;

        /**
        checks all triggers and appropriately pushes events to queue
        */
        void process_triggers(int flags); 
        
        /**
        processes a single event
        */
        void process_event(Event e); 

        /**
        Updates graph and sets flags as appropriate
        */
        void update_graph(int &flags);

        /**
        Sends signal to stop adding to event_queue
        */
        void stop_simulation(int &flags);

        /**
        writes a graphviz snapshot of the grid state to file
        */
        void grid_snapshot(int &flags);

        /**
        Computes and updates metrics in the given RuleTable
        */
        void calc_metrics(int &flags);

        /**** STATE VARIABLES ****/
        int cur_time;
        int max_steps;
        std::map<size_t, int> chksum_map; //(hash, time_step) map, for preserving state
        std::map<std::string, Property> sim_metrics; //map for tracking Simulator metrics
};

#endif 
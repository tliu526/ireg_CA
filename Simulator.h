/*
Simulates the computation. Holds a grid generator for fast reading and writing to file.

Things to think about:
- Scripting capability

TODOs:
- Detecting repeated/periodic states

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
            UPDATE_GRAPH = 1,
            CALC_METRICS = 2,
            STOP_SIMULATION = 4,
            UPDATE_DISPLAY = 8,
            WRITE_TO_FILE = 16,
        } Event;

        //TODO a struct of options to pass
        Simulator(GridGenerator* g, RuleTable* r, int max, std::string file);
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

    protected:
        GridGenerator* generator;
        Graph<std::string, Cell>* grid;
        RuleTable* rule_table;

        std::queue<Event> event_queue;

        //whether or not the simulation is running
        bool running;

        //output file for metrics
        std::string stats_file;

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
        Computes and updates metrics in the given RuleTable
        */
        void calc_metrics(int &flags);

        /**** STATE VARIABLES ****/
        int cur_time;
        int max_steps;
        //TODO module for keeping track of all statistics
        //float lambda;

        //TODO md5
        std::map<size_t, int> chksum_map;
};

#endif 
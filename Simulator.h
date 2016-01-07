/*
Simulates the computation. Holds a grid generator for fast reading and writing to file.

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
            UPDATE_GRAPH = 1,
            CALC_METRICS = 2,
            STOP_SIMULATION = 4,
            UPDATE_DISPLAY = 8,
            WRITE_TO_FILE = 16,
        } Event;

        Simulator(GridGenerator* g, RuleTable* r); //TODO a struct of options to pass
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

    protected:
        GridGenerator* generator;
        Graph<std::string, Cell>* grid;
        RuleTable* rule_table;
        std::queue<Event> event_queue;

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

        /**** STATE VARIABLES ****/
        int cur_time;
        int max_steps;
        //TODO module for keeping track of all statistics
        //float lambda;
        std::map<unsigned int, int> chksum_map;
};

#endif 
/*
Simulates the computation. Holds a grid generator for fast reading and writing to file.

Things to think about:
- Scripting capability

(c) 2015 Tony Liu.
*/

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "GridGenerator.h"

#include <queue>
#include <map>
#include <string>

typedef enum Event {
	UPDATE_GRAPH,
	CALC_METRICS,
	STOP_SIMULATION,
	UPDATE_DISPLAY,
	WRITE_TO_FILE,
} Event;

class Simulator {
	public:
		Simulator(GridGenerator& g, RuleTable& r); 
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
		Graph* grid;
		RuleTable* rule_table;
		std::queue<Event> event_queue;
		
		void process_triggers(int flags); //checks all triggers and appropriately pushes events to queue
		void process_event(Event e); //processes a single event

		/**** STATE VARIABLES ****/
		int cur_time;
		float lambda;
		std::map<unsigned int, int> chksum_map;
};


#endif 
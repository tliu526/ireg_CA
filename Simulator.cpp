/*
Implementation of the Simulator class. Currently pseudocode.

(c) 2016 Tony Liu.
*/

#include "Simulator.h"

using namespace std;

void Simulator::simulate() {

	while(!event_queue.empty()){
		//process top of queue
	}
}

void Simulator::process_event(Event e){

	//set trigger flags after processing each event
	int trigger_flags = 0;

	switch (e) {
		case UPDATE_GRAPH:
		update_graph();
		//set trigger_flag to update_display and update_stats;
		break;

		case WRITE_TO_FILE:
		stats_to_file();
		//set trigger_flag for what?;		
		break;

		//TODO the rest of the cases
		default:
		break;
	}

	process_triggers(trigger_flags);
}

void Simulator::process_triggers(int flags) {
	//for each flag set, push event onto the queue
}


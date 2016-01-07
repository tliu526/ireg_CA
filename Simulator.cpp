/*
Implementation of the Simulator class. Currently pseudocode.

(c) 2016 Tony Liu.
*/

#include "Simulator.h"

#include "SimpleMajorityRule.h"
#include "DelaunayGridGenerator.h"

//for main (Debugging)
static bool debug = true;
#define dout if(debug) cout

using namespace std;

Simulator::Simulator(GridGenerator* g, RuleTable* r) :
    generator(g),
    rule_table(r)
{
    grid = generator->get_graph();
    cur_time = 0;
    max_steps = 10; //TODO abstract to options
}

void Simulator::simulate() {

    rule_table->initialize();
    event_queue.push(UPDATE_GRAPH);

    while(!event_queue.empty()){
        Event e = event_queue.front();
        event_queue.pop();
        process_event(e);
    }

    dout << "Finished simulation" << endl;
}

void Simulator::process_event(Event e){

    //set trigger flags after processing each event, will be a bit mask
    int trigger_flags = 0;

    switch (e) {
        case UPDATE_GRAPH:
        update_graph(trigger_flags);
        break;

        case WRITE_TO_FILE:
        //stats_to_file();
        //set trigger_flag for what?;       
        break;

        //TODO the rest of the cases
        default:
        break;
    }

    process_triggers(trigger_flags);
}

void Simulator::process_triggers(int flags) {
    if(flags & UPDATE_GRAPH) {
        event_queue.push(UPDATE_GRAPH);
    }
    //TODO the rest of the elseifs
}

void Simulator::update_graph(int &flags){
    rule_table->transition();
    dout << "Current time step: " << cur_time << endl;
    cur_time++;
    if(cur_time < max_steps){
        flags |= UPDATE_GRAPH;   
    } 

}

int main() {
    vector<Point> pts = generate_poisson_disk(100, 100, 30, 3);
    DelaunayGridGenerator gen(pts, 0, 100, 0, 100);
    SimpleMajorityRule rule(gen.get_graph());
    Simulator s(&gen, &rule);
    s.simulate();
}

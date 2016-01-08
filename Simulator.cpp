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

Simulator::Simulator(GridGenerator* g, RuleTable* r, int max) :
    generator(g),
    rule_table(r)
{
    grid = generator->get_graph();
    cur_time = 0;
    running = false;
    max_steps = max; //TODO abstract to options
}

void Simulator::simulate() {

    rule_table->initialize();
    event_queue.push(UPDATE_GRAPH);
    running = true;

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

        case CALC_METRICS:
        calc_metrics(trigger_flags);
        break;

        case WRITE_TO_FILE:
        //TODOOO
        //stats_to_file();
        //set trigger_flag for what?;       
        break;

        case STOP_SIMULATION:
        stop_simulation(trigger_flags);
        break;

        default:
        break;
    }

    process_triggers(trigger_flags);
}

//only processes more triggers if the simulation is running
void Simulator::process_triggers(int flags) {
    if(running){
        if (flags & STOP_SIMULATION) {
            event_queue.push(STOP_SIMULATION);
        }
        if(flags & UPDATE_GRAPH) {
            event_queue.push(UPDATE_GRAPH);
        }
     
    }
}

void Simulator::update_graph(int &flags){
    rule_table->transition();
    dout << "Current time step: " << cur_time << endl;
    cur_time++;
    
    size_t chksum = rule_table->get_grid_state();

    //TODO other things here, such as check period length (can be done with cur_time)
    if(chksum_map.count(chksum) > 0){
        flags |= (STOP_SIMULATION | CALC_METRICS | WRITE_TO_FILE);
    }
    else {
        chksum_map[chksum] = cur_time;
    }

    if(cur_time < max_steps){
        flags |= UPDATE_GRAPH;   
    } 
}

void Simulator::stop_simulation(int &flags){
    running = false;
    flags = 0;
}

void Simulator::calc_metrics(int &flags) {
    rule_table->compute_metrics();
}

int main() {
    vector<Point> pts = generate_poisson_disk(100, 100, 30, 3.5, 123);
    //vector<Point> pts = generate_uniform_rand(500, 100, 100, 10);
    DelaunayGridGenerator gen(pts, 0, 100, 0, 100);
    SimpleMajorityRule rule(gen.get_graph(), 0.85, 12);

    Simulator s(&gen, &rule, 50);
    s.simulate();
}

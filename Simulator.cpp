/*
Implementation of the Simulator class.

(c) 2016 Tony Liu.
*/

#include "Simulator.h"

#include "SimpleMajorityRule.h"
#include "DelaunayGridGenerator.h"

#include <fstream>

//for main (Debugging)
static bool debug = false;
#define dout if(debug) cout

using namespace std;

Simulator::Simulator(GridGenerator* g, RuleTable* r, int max, string f) :
    generator(g),
    rule_table(r)
{
    grid = generator->get_graph();
    cur_time = 0;
    running = false;

    //TODO abstract to options
    max_steps = max;
    stats_file = f;
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

//    dout << "Finished simulation" << endl;
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
        stats_to_file();
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
        //STOP_SIMULATION needs to be first
        if (flags & STOP_SIMULATION) event_queue.push(STOP_SIMULATION);
        if (flags & UPDATE_GRAPH) event_queue.push(UPDATE_GRAPH);
        if (flags & CALC_METRICS) event_queue.push(CALC_METRICS);
        if (flags & WRITE_TO_FILE) event_queue.push(WRITE_TO_FILE);
    }
}

void Simulator::update_graph(int &flags){
    rule_table->transition();
  //  dout << "Current time step: " << cur_time << endl;
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
    else {
        flags |= (CALC_METRICS | WRITE_TO_FILE);
    }
}

void Simulator::stop_simulation(int &flags){
    running = false;
    flags = 0;
}

void Simulator::calc_metrics(int &flags) {
    rule_table->compute_metrics();
}

void Simulator::stats_to_file(){
    fstream file;
    string delim = " ";

    file.open(stats_file, fstream::in | fstream::out | fstream::app);

    map<string, Property>* metrics = rule_table->get_metrics();
    typename map<string, Property>::iterator map_it;

    for(map_it = metrics->begin(); map_it != metrics->end(); map_it++){
        file << map_it->second.to_string() << delim;
    }

    file << cur_time << endl;

    file.close();
}


/*
int main() {
    vector<Point> pts = generate_poisson_disk(15, 15, 30, 0.75, 120);
    //vector<Point> pts = generate_uniform_rand(250, 8, 8, 9);
    DelaunayGridGenerator gen(pts, 0, 15, 0, 15);
    gen.grid_to_file("sim_test.txt");
    gen.grid_to_dot("sim_test");
    SimpleMajorityRule rule(gen.get_graph(), 0.45, 34);

    Simulator s(&gen, &rule, 250, "stat_test.txt");
    s.simulate();
}
*/
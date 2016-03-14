/*
Implementation of the Simulator class.

TODO:
- add period to state variables.

(c) 2016 Tony Liu.
*/

#include "Simulator.h"

#include "SimpleMajorityRule.h"
#include "DelaunayGridGenerator.h"
#include "SimpleLifeRule.h"

#include <fstream>

//for main (Debugging)
static bool debug = false;
#define dout if(debug) cout

using namespace std;

const string Simulator::STATS_EXTENSION = ".csv";
const string Simulator::STATS_DELIM = " ";
const string Simulator::TIME = "Time";
const string Simulator::PERIOD = "Period";

Simulator::Simulator(GridGenerator* g, RuleTable* r, int max, string f, int snapshot, int stats) :
    generator(g),
    rule_table(r)
{
    grid = generator->get_graph();
    cur_time = 0;
    running = false;

    //TODO abstract to options
    max_steps = max;
    out_file = f;
    snapshot_freq = snapshot;
    stats_freq = stats;

    //initialize sim_metrics
    Property timestep(TIME, cur_time);
    Property period(PERIOD, int(0));

    sim_metrics[TIME] = timestep;
    sim_metrics[PERIOD] = period;

    rule_table->initialize();
}

void Simulator::simulate() {

    if(snapshot_freq) event_queue.push(GRID_SNAPSHOT);
    event_queue.push(UPDATE_GRAPH);
    running = true;
    //metric_headers();

    while(!event_queue.empty()){
        Event e = event_queue.front();
        event_queue.pop();
        process_event(e);
    }

    dout << "Finished simulation" << endl;
}

void Simulator::process_event(Event e){

    //set trigger flags after processing each event
    int trigger_flags = 0;

    switch (e) {
        case UPDATE_GRAPH:
        update_graph(trigger_flags);
        break;

        case CALC_METRICS:
        calc_metrics(trigger_flags);
        break;

        case STATS_TO_FILE:
        stats_to_file();
        break;

        case STOP_SIMULATION:
        stop_simulation(trigger_flags);
        break;

        case GRID_SNAPSHOT:
        grid_snapshot(trigger_flags);
        break;

        default:
        break;
    }

    process_triggers(trigger_flags);
}

//only processes more triggers if the simulation is running
void Simulator::process_triggers(int flags) {

    //STOP_SIMULATION needs to be first
    if (flags & STOP_SIMULATION) event_queue.push(STOP_SIMULATION);    
    if (flags & CALC_METRICS) event_queue.push(CALC_METRICS);
    if (flags & STATS_TO_FILE) event_queue.push(STATS_TO_FILE);
    if (flags & GRID_SNAPSHOT) event_queue.push(GRID_SNAPSHOT);

    //UPDATE_GRAPH needs to be last
    if (running && flags & UPDATE_GRAPH) event_queue.push(UPDATE_GRAPH);
}

void Simulator::update_graph(int &flags){
    rule_table->transition();
    dout << "Current time step: " << cur_time << endl;
    cur_time++;
    size_t chksum = rule_table->get_grid_state();

    if(stats_freq){
        if((cur_time % stats_freq) == 0){
            flags |= (STATS_TO_FILE | CALC_METRICS);
        }
    }

    if(snapshot_freq){
        if((cur_time % snapshot_freq) == 0){
            flags |= GRID_SNAPSHOT;
        }
    }

    if(chksum_map.count(chksum) > 0){
        flags |= STOP_SIMULATION;
        int period = cur_time - chksum_map[chksum];
        sim_metrics[PERIOD].set_int(period);
        dout << "Repeated state" << endl;
    }
    else {
        chksum_map[chksum] = cur_time;

        if(cur_time < max_steps){
            flags |= UPDATE_GRAPH;   
        } 
        else {
            flags |= STOP_SIMULATION;
        }
    }
}

//TODO other flags that need to be set here
void Simulator::stop_simulation(int &flags){
    running = false;
    flags |= (CALC_METRICS | STATS_TO_FILE);
    
    //can get rid of this for end of simulation snapshot
    if(snapshot_freq){
        flags |= GRID_SNAPSHOT;
    }
}

void Simulator::calc_metrics(int &flags) {
    sim_metrics[TIME].set_int(cur_time);

    rule_table->compute_metrics();
}

void Simulator::stats_to_file(){
    fstream file;

    file.open(out_file+STATS_EXTENSION, fstream::in | fstream::out | fstream::app);

    //RuleTable metrics
    map<string, Property>* metrics = rule_table->get_metrics();
    typename map<string, Property>::iterator map_it;

    for(map_it = metrics->begin(); map_it != metrics->end(); map_it++){
        file << map_it->second.to_string() << STATS_DELIM;
    }

    //Simulator state variables
    for(map_it = sim_metrics.begin(); map_it != sim_metrics.end(); map_it++){
        file << map_it->second.to_string() << STATS_DELIM;
    }

    file << endl;

    file.close();
}

//TODO how to make unique for each run of the simulator?
//snapshot_id member variable?
void Simulator::grid_snapshot(int &flags) {
    string filename = out_file+"_"+to_string(cur_time);
    string label = "Timestep "+to_string(cur_time);
    generator->grid_to_dot(filename, label);
}

void Simulator::metric_headers() {
    fstream file;

    file.open(out_file+STATS_EXTENSION, fstream::in | fstream::out | fstream::trunc);

    //RuleTable stat headers
    map<string, Property>* metrics = rule_table->get_metrics();
    typename map<string, Property>::iterator map_it;

    for(map_it = metrics->begin(); map_it != metrics->end(); map_it++){
        file << map_it->first << STATS_DELIM;
    }

    //Simulator stat headers
    for(map_it = sim_metrics.begin(); map_it != sim_metrics.end(); map_it++){
        file << map_it->first << STATS_DELIM;
    }
    file << endl;

    file.close();
}

/*
int main() {
    vector<Point> pts = generate_poisson_disk(15, 15, 30, 0.75, 120);
    //vector<Point> pts = generate_uniform_rand(250, 8, 8, 9);
    DelaunayGridGenerator gen(pts, 0, 15, 0, 15);
    SimpleLifeRule rule(gen.get_graph(), 0.45, 34);

    Simulator s(&gen, &rule, 250, "sim_test");
    s.metric_headers();
    s.simulate();
}
*/

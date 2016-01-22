/*
Implementation of the GridGenerator class.

(c) Tony Liu 2015.
*/
#include "GridGenerator.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const string GridGenerator::B_STATE = "B:State";
const string GridGenerator::I_STATE = "I:State";
const string GridGenerator::F_STATE = "F:State";
const int GridGenerator::FONT_SIZE = 90;
GridGenerator::GridGenerator(vector<Point>& p, float min_x, float max_x, float min_y, float max_y) :
	gen_pts(p), 
	max_x(max_x),
	max_y(max_y),
	min_x(min_x),
	min_y(min_y)
	{}

GridGenerator::GridGenerator(string file){
	init_from_file(file);
}

void GridGenerator::init_from_file(string file){
	string line, name, coord, neighbor, prop;
	int n;
	bool isAlive;
	istringstream iss;
	ifstream in(file);
	map<string, vector<string>> neighbor_map;
	
	/**** BOUNDARY ****/
	getline(in, line);
	iss.str(line);
	iss.clear();

	//store into member variables
	iss >> grid_type;
	iss >> min_x >> max_x >> min_y >> max_y;	

	/**** GEN POINTS ****/
	getline(in, line);

	iss.str(line);
	iss.clear();
	iss >> name >> n;

	//Grab all the attributes
	vector<string> prop_labels;
	getline(in, line);
	iss.str(line);
	iss.clear();
	iss >> name >> coord >> prop;

	while(prop.compare("Neighbors") != 0){
		prop_labels.push_back(prop);
		iss >> prop;
	}

	for (size_t i = 0; i < n; i++){
		getline(in,line);
		iss.str(line);
		iss.clear();

		iss >> name >> coord;

		//Build properties vector
		vector<Property> properties;
	    for (size_t i = 0; i < prop_labels.size(); i++){
	    	iss >> prop;
	    	properties.push_back(build_property(prop_labels[i], prop));
	    }

		//TODO something's up with mingw
		//float x = stof(coord.substr(0, coord.find(","));
		//float y = stof(coord.substr(coord.find(",")+1, coord.size());

		float x = atof(coord.substr(0, coord.find(",")).c_str());
		float y = atof(coord.substr(coord.find(",")+1, coord.size()).c_str());

		Point p(x,y);
		gen_pts.push_back(p);
		pt_map[name] = p;
		rev_gen_pt_map[p] = name;
		//graph.add_vertex(name, Cell(p, name, isAlive));
		graph.add_vertex(name, Cell(p, name, properties));

	    //Collect neighbors of each gen_pt
		while(!iss.eof()){
			iss >> neighbor;
			neighbor_map[name].push_back(neighbor);
		}
        
	}

	getline(in, line);
	
	/**** GRAPH ****/
	typename map<string, vector<string>>::iterator map_it;
	for(map_it = neighbor_map.begin(); map_it != neighbor_map.end(); map_it++){
		vector<string>* v = &map_it->second;
		for(size_t i = 0; i < v->size(); i++){
			graph.add_edge(map_it->first, (*v)[i]);
		}
	}

	/**** VERTS ****/
	getline(in, line);
	iss.str(line);
	iss.clear();
	iss >> name >> n;

	for (size_t i = 0; i < n; i++){
		getline(in, line);
		iss.str(line);
		iss.clear();

		iss >> name >> coord;

		float x = atof(coord.substr(0, coord.find(",")).c_str());
		float y = atof(coord.substr(coord.find(",")+1, coord.size()).c_str());

		Point p(x,y);

		verts.push_back(p);
		pt_map[name] = p;
		rev_vert_map[p] = name;
	}

	getline(in, line);

	/**** EDGES ****/
	string p, q;
	getline(in, line);
	
	iss.str(line);
	iss.clear();
	iss >> name >> n;

	for(size_t i = 0; i < n; i++){
		getline(in, line);
		iss.str(line);
		iss.clear();

		iss >> name >> p >> q;
		Edge e(pt_map[p], pt_map[q]);
		edges.push_back(e);
		edge_map[name] = e;
		rev_edge_map[e] = name;

		graph.add_edge(rev_gen_pt_map[pt_map[p]], rev_gen_pt_map[pt_map[q]]);
	}

	getline(in, line);

	/**** FACES ****/
	string e_label;
	getline(in, line);
	iss.str(line);
	iss.clear();
	iss >> name >> n;

	for (int i = 0; i < n; i++){
		getline(in, line);
		iss.str(line);
		iss.clear();


		iss >> name;
		vector<Edge> face_edges;
		while(!iss.eof()){
			iss >> e_label;
			face_edges.push_back(edge_map[e_label]);
		}

		Poly face(face_edges);
		faces.push_back(face);
		face_map[name] = face;
	}
}

void GridGenerator::init_maps(){

	//rev_gen_pt_map
	for (size_t i = 0; i < gen_pts.size(); i++) {
		stringstream ss;
		ss << "gp";
		
		int n = digit_diff(i, gen_pts.size());
		while(n--) { ss << "0"; }
			
		ss << i; 
		rev_gen_pt_map[gen_pts[i]] = ss.str();
	}

	//rev_vert_map
	for (size_t i = 0; i < verts.size(); i++) {
		stringstream ss;
		ss << "p";
		
		int n = digit_diff(i, verts.size());
		while(n--) { ss << "0"; }
			
		ss << i; 
		rev_vert_map[verts[i]] = ss.str();
	}

	//rev_edge_map
	for (size_t i = 0; i < edges.size(); i++) {
		stringstream ss;
		ss << "e";
		
		int n = digit_diff(i, edges.size());
		while(n--) { ss << "0"; }
			
		ss << i; 
		rev_edge_map[edges[i]] = ss.str();
	}

	//TODO vert_map, edge_map, face_map
	/*
	for (int i = 0; i < faces.size(); i++) {
		stringstream ss;
		ss << "f";

		int n = digit_diff(i, faces.size());
		while(n--) { ss << "0"; }
			
		ss << i; 
		face_map[faces[i]] = ss.str();
	}
	*/
}

void GridGenerator::grid_to_file(string f){
	ofstream file;
	file.open(f+".txt");

	file << grid_type << " ";
	file << min_x << " " << max_x << " " ;
	file << min_y << " " << max_y << endl;

	/**** CELLS ****/
	file << "GenPoints" << " " << gen_pts.size() << endl;
	file << "Label" << " " << "Point" << " ";

	//Writes all the present properties to the header of the file
	//Assumes all the cells have the same properties, TODO safe assumption?
	map<string, Property>* prop_map = graph.get_data(rev_gen_pt_map[gen_pts[0]])->get_prop_map();
    typename map<string, Property>::iterator map_it;
    for (map_it = prop_map->begin(); map_it != prop_map->end(); map_it++) {
    	file << map_it->first << " "; 
    }

	file << "Neighbors" << endl;

	for (size_t i = 0; i < gen_pts.size(); i++){
		string p_id = rev_gen_pt_map[gen_pts[i]];
		Cell *c = graph.get_data(p_id);
		file << p_id << " " << gen_pts[i] << " "; //<< c.is_alive();


		map<string, Property>* prop_map = c->get_prop_map();
		typename map<string, Property>::iterator map_it;
		for (map_it = prop_map->begin(); map_it != prop_map->end(); map_it++) {
			file << (map_it->second).to_string() << " "; 
		}

		typename list<string>::iterator list_it;
		list<string>* neighbors = graph.get_neighbors(p_id);
		
		for (list_it = neighbors->begin(); list_it != neighbors->end(); list_it++) {
			//file << " " << *list_it;
			//TODO will trailing space mess things up?
			file << *list_it << " ";
		}

		file << endl;
	}

	file << endl;

	/**** VERTICES ****/
	file << "Vertices" << " " << verts.size() << endl;
	for (size_t i = 0; i < verts.size(); i++){
		string v_id = rev_vert_map[verts[i]];
		file << v_id << " " << verts[i] << endl;
	}

	file << endl;

	/**** EDGES ****/
	file << "Edges" << " " << edges.size() << endl;
	//file << "Label" << " " << "p" << " " << "q" << endl;

	for (size_t i = 0; i < edges.size(); i++){
		string e_id = rev_edge_map[edges[i]];
		file << e_id << " " << rev_vert_map[edges[i].p] << " " << rev_vert_map[edges[i].q] << endl;
	}

	file << endl;
	/**** FACES ****/
	file << "Faces" << " " << faces.size() << endl;
	//file << "Label" << " " << "Edges" << endl;

	for (size_t i = 0; i < faces.size(); i++) {
		stringstream ss;
		ss << "f";
		
		int n = digit_diff(i, faces.size());
		while(n--) { ss << "0"; }			
		ss << i; 

		string f_id = ss.str();
		file << f_id;
		vector<Edge> edge_vec(faces[i].edges);
		for (size_t j = 0; j < edge_vec.size(); j++){
			file << " " << rev_edge_map[edge_vec[j]];
		}

		file << endl;
	}

	file.close();
}

void GridGenerator::grid_to_dot(string name, string label/* = "" */){
	ofstream file;
	file.open(name+".dot");
	file << "Graph G {" << endl;
	file << "labelloc = b;" << endl;
	file << "fontsize = " + to_string(FONT_SIZE) << ";" << endl;
	file << "label = \"" << label << "\";" << endl;
	file << "node [shape=circle, style=filled, width=0.25, height=0.25, fixedsize=true, label=\"\"];" << endl;


	//verts
	for (size_t i = 0; i < verts.size(); i++){
		string v_id = rev_vert_map[verts[i]];
		stringstream ss;
		ss << verts[i];
		string coord = ss.str();
		file << v_id << " [pos = \"" << coord << "!\"];" << endl;
	}

	file << endl;

	//gen_pts
	for (size_t i = 0; i < gen_pts.size(); i++) {
		string gp_id = rev_gen_pt_map[gen_pts[i]];
		stringstream ss;
		ss << gen_pts[i];
		string coord = ss.str();
		file << gp_id << " [pos = \"" << coord << "!\" ";
		
		map<string, Property>* prop_map = graph.get_data(gp_id)->get_prop_map();
		//TODO abstract to function
		if(prop_map->count(B_STATE) > 0) {
			Property p = graph.get_data(gp_id)->get_property(B_STATE);
			if(p.b){
				file << "fillcolor=\"black\"";
			}
		}

		file << "];" << endl;
	}

	file << endl;

	//edges
	for (size_t i = 0; i < edges.size(); i++){
		file << rev_vert_map[edges[i].p] << " -- " << rev_vert_map[edges[i].q] << ";" << endl;
	}

	file << "}" << endl;

	file.close();
}

void GridGenerator::graph_to_dot(string name, string label){
	ofstream file;
	file.open(name+".dot");
	file << "Graph G {" << endl;
	file << "labelloc = b;" << endl;
	file << "fontsize = " + to_string(FONT_SIZE) << ";" << endl;
	file << "label = \"" << label << "\";" << endl;
	file << "node [shape=circle, style=filled, width=0.25, height=0.25, fixedsize=true, label=\"\"];" << endl;

	//gen_pts
	for (size_t i = 0; i < gen_pts.size(); i++) {
		string gp_id = rev_gen_pt_map[gen_pts[i]];
		stringstream ss;
		ss << gen_pts[i];
		string coord = ss.str();
		file << gp_id << " [pos = \"" << coord << "!\" ";
		
		map<string, Property>* prop_map = graph.get_data(gp_id)->get_prop_map();

		//TODO abstract to function
		if(prop_map->count(B_STATE) > 0) {
			Property p = graph.get_data(gp_id)->get_property(B_STATE);
			if(p.b){
				file << "fillcolor=\"black\"";
			}
		}

		file << "];" << endl;
	}

	file << endl;

	//edges
	vector<string> labels = graph.get_vert_labels();
	for(size_t i = 0; i < labels.size(); i++){
		list<string>* neighbors = graph.get_neighbors(labels[i]);

		typename list<string>::iterator list_it;
		for(list_it = neighbors->begin(); list_it != neighbors->end(); list_it++){
			if(count(labels.begin(), labels.begin()+i, *list_it) == 0) {
				file << labels[i] << " -- " << *list_it << ";" << endl;
			}
		}
	}

	file << "}" << endl;

	file.close();
}

bool GridGenerator::pt_in_grid(Point p) {
	return (p.x < max_x) && (p.x > min_x) && (p.y < max_y) && (p.y > min_y);
}

vector<Poly> GridGenerator::get_faces(){
	return faces;
}

Graph<string, Cell>* GridGenerator::get_graph() {
	return &graph;
}

void GridGenerator::generate_graph(){
	//does nothing, TODO abstract?
}

Property GridGenerator::build_property(std::string& name, std::string& value) {
	char tag;
	string label;

	tag = name.at(0);
	label = name.substr(2);

	switch(tag){
		case Property::INT:
		return Property(label, stoi(value));

		case Property::BOOL:
		return Property(label, bool(stoi(value)));

		case Property::FLOAT:
		return Property(label, stof(value));

		default:
		break;
	}

	return Property();
}

//assigns a gen_pt to the face that is closest to it (by avg vertex distance)
void GridGenerator::map_faces() {
	//init vector of faces
	vector<string> face_labels;
	typename map<string, Poly>::iterator face_it;

	for(face_it = face_map.begin(); face_it != face_map.end(); face_it++){
		face_labels.push_back(face_it->first);
	}

	//build gen_pt_face_map
	for(size_t i = 0; i < gen_pts.size(); i++){
		
		float min_dist = HUGE_VALF;
		string closest_face;
		for(size_t j = 0; j < face_labels.size(); j++){
			float avg = 0;
			Poly face = face_map[face_labels[j]];
			vector<Point>* verts = &face.verts;

			for (size_t k = 0; k < verts->size(); k++) {
				avg += distance(gen_pts[i], (*verts)[k]);
			}
			avg /= verts->size();

			if (avg < min_dist) {
				min_dist = avg;
				closest_face = face_labels[j];
			}
		}

		gen_pt_face_map[rev_gen_pt_map[gen_pts[i]]] = closest_face;
	}

	//debugging
/*
	typename map<string, string>::iterator map_it;
	for(map_it = gen_pt_face_map.begin(); map_it != gen_pt_face_map.end(); map_it++){
		cout << "(" << map_it->first << ", " << map_it->second << ")" << endl;
	}
*/
}
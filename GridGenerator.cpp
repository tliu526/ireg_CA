/*
Filling out GridGenerator abstract class. Currently the only function that is implemented here is 
graph_to_file.

(c) Tony Liu 2015.
*/
#include "GridGenerator.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

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
	string line, name, coord, neighbor;
	int n;
	bool isAlive;
	istringstream iss;
	ifstream in(file);
	
	/**** BOUNDARY ****/
	getline(in, line);
	iss.str(line);
	iss.clear();
	iss >> name;

	iss >> min_x >> max_x >> min_y >> max_y;	

	/**** GEN POINTS ****/
	getline(in, line);

	iss.str(line);
	iss.clear();
	iss >> name >> n;

	//TODO attributes, this line is ignored for now
	getline(in, line);

	for (int i = 0; i < n; i++){
		getline(in,line);
		iss.str(line);
		iss.clear();

		iss >> name >> coord >> isAlive;

		//TODO attribute list
		/*
	    while(n){
	        iss >> attr;
	        //do something
	    }
		*/

		//TODO something's up with mingw
		//float x = stof(coord.substr(0, coord.find(","));
		//float y = stof(coord.substr(coord.find(",")+1, coord.size());

		float x = atof(coord.substr(0, coord.find(",")).c_str());
		float y = atof(coord.substr(coord.find(",")+1, coord.size()).c_str());

		Point p(x,y);
		gen_pts.push_back(p);
		pt_map[name] = p;
		rev_gen_pt_map[p] = name;
		graph.add_vertex(name, Cell(p, name, isAlive));

	    /*
		while(!iss.eof()){
			iss >> neighbor;
			//cout << neighbor << " ";
		}
        */
	}

	getline(in, line);
	
	/**** VERTS ****/
	getline(in, line);
	iss.str(line);
	iss.clear();
	iss >> name >> n;

	for (int i = 0; i < n; i++){
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

	for(int i = 0; i < n; i++){
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
	for (int i = 0; i < gen_pts.size(); i++) {
		stringstream ss;
		ss << "gp";
		
		int n = digit_diff(i, gen_pts.size());
		while(n--) { ss << "0"; }
			
		ss << i; 
		rev_gen_pt_map[gen_pts[i]] = ss.str();
	}

	//rev_vert_map
	for (int i = 0; i < verts.size(); i++) {
		stringstream ss;
		ss << "p";
		
		int n = digit_diff(i, verts.size());
		while(n--) { ss << "0"; }
			
		ss << i; 
		rev_vert_map[verts[i]] = ss.str();
	}

	//rev_edge_map
	for (int i = 0; i < edges.size(); i++) {
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
	file.open(f);

	file << grid_type << " ";
	file << min_x << " " << max_x << " " ;
	file << min_y << " " << max_y << endl;

	/**** CELLS ****/
	file << "GenPoints" << " " << gen_pts.size() << endl;
	file << "Label" << " " << "Point" << " " << "isAlive" << " ";
	//TODO property list
	file << "Neighbors" << endl;

	for (int i = 0; i < gen_pts.size(); i++){
		string p_id = rev_gen_pt_map[gen_pts[i]];
		Cell c = graph.get_data(p_id);
		file << p_id << " " << gen_pts[i] << " " << c.is_alive();

		//TODO print property list

		typename list<string>::iterator list_it;
		list<string>* neighbors = graph.get_neighbors(p_id);
		
		for (list_it = neighbors->begin(); list_it != neighbors->end(); list_it++) {
			file << " " << *list_it;
		}

		file << endl;
	}

	file << endl;

	/**** VERTICES ****/
	file << "Vertices" << " " << verts.size() << endl;
	for (int i = 0; i < verts.size(); i++){
		string v_id = rev_vert_map[verts[i]];
		file << v_id << " " << verts[i] << endl;
	}

	file << endl;

	/**** EDGES ****/
	file << "Edges" << " " << edges.size() << endl;
	//file << "Label" << " " << "p" << " " << "q" << endl;

	for (int i = 0; i < edges.size(); i++){
		string e_id = rev_edge_map[edges[i]];
		file << e_id << " " << rev_vert_map[edges[i].p] << " " << rev_vert_map[edges[i].q] << endl;
	}

	file << endl;
	/**** FACES ****/
	file << "Faces" << " " << faces.size() << endl;
	//file << "Label" << " " << "Edges" << endl;

	for (int i = 0; i < faces.size(); i++) {
		stringstream ss;
		ss << "f";
		
		int n = digit_diff(i, faces.size());
		while(n--) { ss << "0"; }			
		ss << i; 

		string f_id = ss.str();
		file << f_id;
		vector<Edge> edge_vec(faces[i].edges);
		for (int j = 0; j < edge_vec.size(); j++){
			file << " " << rev_edge_map[edge_vec[j]];
		}

		file << endl;
	}

	file.close();
}

void GridGenerator::grid_to_dot(string name){
	ofstream file;
	file.open(name+".dot");
	file << "Graph G {" << endl;
	file << "node [shape = circle, style=filled, width=0.05, height=0.05];" << endl;


	for (int i = 0; i < verts.size(); i++){
		string v_id = rev_vert_map[verts[i]];
		stringstream ss;
		ss << verts[i];
		string coord = ss.str();
		//coord = coord.substr(1, coord.size()-2);
		//cout << "Coord: " << coord << endl;
		file << v_id << " [pos = \"" << coord << "!\"];" << endl;
	}

	file << endl;

	for (int i = 0; i < edges.size(); i++){
		file << rev_vert_map[edges[i].p] << " -- " << rev_vert_map[edges[i].q] << ";" << endl;
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

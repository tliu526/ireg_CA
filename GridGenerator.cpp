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

GridGenerator::GridGenerator(vector<Point>& p) :
	gen_pts(p) 
	{}

GridGenerator::GridGenerator(string file){
	//TODO (needed?)
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

	//face_map
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

vector<Poly> GridGenerator::get_faces(){
	return faces;
}

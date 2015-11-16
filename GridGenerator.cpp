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

void GridGenerator::init_maps(){

	//pt_map
	for (int i = 0; i < verts.size(); i++) {
		stringstream ss;
		ss << "p";
		
		int n = digit_diff(i, verts.size());
		while(n--) { ss << "0"; }
			
		ss << i; 
		pt_map[verts[i]] = ss.str();
	}
//TODO add < comparators
/*
	//edge_map
	for (int i = 0; i < edges.size(); i++) {
		stringstream ss;
		ss << "e";
		
		int n = digit_diff(i, edges.size());
		while(n--) { ss << "0"; }
			
		ss << i; 
		edge_map[edges[i]] = ss.str();
	}

	//face_map
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

	/**** POINTS/CELLS ****/
	file << "Points" << " " << verts.size() << endl;
	file << "Label" << " " << "Point" << " " << "isAlive" << " ";
	//TODO property list
	file << "Neighbors" << endl;

	for (int i = 0; i < verts.size(); i++){
		string id = pt_map[verts[i]];
		Cell c = graph.get_data(id);
		file << id << " " << verts[i] << " " << c.is_alive() << " ";

		//TODO print property list

		typename list<string>::iterator list_it;
		list<string>* neighbors = graph.get_neighbors(id);
		for (list_it = neighbors->begin(); list_it != neighbors->end(); list_it++) {
         file << *list_it << " ";
       }

		file << endl;
	}

	file << endl;

	/**** EDGES ****/


	/**** FACES ****/

	file.close();
}

vector<Poly> GridGenerator::get_faces(){
	return faces;
}

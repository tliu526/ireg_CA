/*
Filling out GridGenerator abstract class. Currently the only function that is implemented here is 
graph_to_file.

(c) Tony Liu 2015.
*/
#include "GridGenerator.h"

using namespace std;

GridGenerator::GridGenerator(vector<Point>& p) :
	gen_pts(p) 
	{}

void GridGenerator::grid_to_file(string f){
	//TODO
}

vector<Poly> GridGenerator::get_faces() {
	return faces;
}

#include "util.h"

#include <random>
#include <iostream>
#include <vector>

using namespace std;

void generate_uniform_rand(vector<point>& pts, int n, float x, float y){
	//TODO investigate other random engines
	default_random_engine gen;
	uniform_real_distribution<double> x_distr(0.0, x);
	uniform_real_distribution<double> y_distr(0.0, y);

	for (int i = 0; i < n; i++){
		pts.push_back(point(x_distr(gen), y_distr(gen)));
	}
}

void generate_poisson_disk(vector<point>& pts, int n, float x, float y, float r){

}

//TODO defining the dimensions?
void pts_to_file(vector<point>& pts, string f){

} 

//For debugging my incompetence in C++
int main() {

	/**** Points generation ****/
	vector<point> points;
	generate_uniform_rand(points, 10, 10.0f, 10.0f);

	for (int i = 0; i < points.size(); i++){
		cout << points[i].first << "," << points[i].second << "\n";
	}

	return 0;
}
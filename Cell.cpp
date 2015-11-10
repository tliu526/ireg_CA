/*
Implementation of Cell class.

(c) Tony Liu 2015.
*/
#include "Cell.h"

#include <iostream>

using namespace std;


int Cell::next_id = 0;

Cell::Cell(point& p) :
	pt(0.0,0.0)
{
	alive = false;
	uid = next_id;
	Cell::next_id++;
}

Cell::Cell() {}

bool Cell::is_alive() {
	return alive; 
}

int Cell::get_uid() {
	return uid;
}

point *Cell::get_point() {
	return &pt;
}

list<int> *Cell::get_neighbors() {
	return &neighbors;
}

void Cell::add_neighbor(int id) {
	neighbors.push_back(id);
}

void Cell::remove_neighbor(int id) {
	neighbors.remove(id);
}
//for debugging because I'm bad at B++
/*
int main() {
	point p(5.0f, 0.1f);
	Cell c(p);
	Cell d(p);

	cout << c.is_alive() << "\n";
	cout << c.get_point()->first << "\n";
	cout << c.get_uid() << "\n";

	cout << d.get_point()->second << "\n";
	cout << d.get_uid() << "\n";
}
*/
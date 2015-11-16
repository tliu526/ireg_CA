/*
Implementation of Cell class.

(c) Tony Liu 2015.
*/
#include "Cell.h"

#include <iostream>

using namespace std;

Cell::Cell(Point p, string label)
{
	alive = false;
	id = label;
	pt = p;
}

bool Cell::is_alive() {
	return alive; 
}

string Cell::get_id() {
	return id;
}

Point Cell::get_point() {
	return pt;
}

//for debugging because I'm bad at B++
int main() {
	Point p(5.0, 0.1);

	Cell c(p, "a");
	Cell d(p, "b");

	cout << c.is_alive() << "\n";
	cout << c.get_point().x << "\n";
	cout << c.get_id() << "\n";

	cout << d.get_point().y << "\n";
	cout << d.get_id() << "\n";
}
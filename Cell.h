/*
Represents the state and contains the information of a single cell on the grid. Currently stores a list
of key value pairs (TODO variable value types), with the intent of being subclassed. The base class Cell
only has one property (is_alive) as well as its label.

(c) Tony Liu 2015.
*/

#ifndef CELL_H
#define CELL_H

#include "util.h"

#include <vector>
#include <map>

class Cell {
public:
	
	Cell(Point p, std::string label);
	Cell() {};
	//TODO other constructors?

	bool        is_alive();
	std::string get_id();
	Point       get_point();

	std::string get_property(std::string label);
protected:
	bool alive;
	Point pt; // the point in the space that corresponds to 
	std::string id;

	//TODO make the value of variable type?
	std::map<std::string, std::string> prop_map;
};

#endif

/*
Represents the state and contains the information of a single cell on the grid. Currently stores a list
of key value pairs (TODO variable value types), with the intent of being subclassed. The base class Cell
only has one property (is_alive) as well as its label.

(c) Tony Liu 2015.
*/

#ifndef CELL_H
#define CELL_H

#include "util.h"
#include "Property.h"

#include <vector>
#include <map>

class Cell {
public:
	
	Cell(Point p, std::string label);
	Cell(Point p, std::string label, bool alive);
	Cell(Point p, std::string label, std::vector<Property>& props);

	Cell() {};
	//TODO other constructors?

	bool        is_alive();
	std::string get_id();
	Point       get_point();

	Property get_property(std::string label);
	void add_property(Property& p);

	std::map<std::string, Property>* get_prop_map();
protected:
	bool alive;
	Point pt; // the point in the space that corresponds to 
	std::string id;

	//Holds the property label, needed?
	//std::vector<std::string> prop_labels;
	std::map<std::string, Property> prop_map;
};

#endif

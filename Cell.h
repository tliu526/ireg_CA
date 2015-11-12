/*
Represents the state and contains the information of a single cell on the grid.

Things to consider:
- What other properties do we need?
- What's the best way of setting UIDs?

(c) Tony Liu 2015.
*/

#ifndef CELL_H
#define CELL_H

#include "util.h"

#include <list>

class Cell {
public:
	
	Cell(point& p);
	Cell();
	//TODO other constructors?

	bool       is_alive();
	int        get_uid();
	point     *get_point();
	std::list<int> *get_neighbors();

	void       add_neighbor(int id);
	void       remove_neighbor(int id);

protected:
	bool alive;
	point pt;
	int uid; 
	std::list<int> neighbors;
	static int next_id;
};

#endif

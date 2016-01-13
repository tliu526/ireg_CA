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

Cell::Cell(Point p, string label, bool a)
{
	alive = a;
	id = label;
	pt = p;
}

Cell::Cell(Point p, string label, vector<Property>& props){
	id = label;
	pt = p;	
	
	for (size_t i = 0; i < props.size(); i++){
		add_property(props[i]);
	//	Property p = props[i];
	//	prop_map[p.get_label()] = p;
	}
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

void Cell::add_property(Property p) {
	prop_map[p.get_label()] = p;
}

Property Cell::get_property(string label){
	if(prop_map.count(label) > 0) {
		return prop_map[label];
	}

	cout << "Property not found" << endl;
}


map<string, Property>* Cell::get_prop_map(){
	return &prop_map;
}

/*
//for debugging because I'm bad at C++
int main() {
	Point p(5.0, 0.1);

	Cell c(p, "a");
	Cell d(p, "b");

	cout << c.is_alive() << "\n";
	cout << c.get_point().x << "\n";
	cout << c.get_id() << "\n";

	cout << d.get_point().y << "\n";
	cout << d.get_id() << "\n";

	vector<Property> v;
	v.push_back(Property("is_alive", false));
	
	Cell cell(p, "test", v);

	Property prop = cell.get_property("is_alive");
	cout << "is_alive " << prop.to_string() << endl;
}
*/
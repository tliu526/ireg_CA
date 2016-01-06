/*
The implementation of Property (a discriminated union).

(c) 2016 Tony Liu
*/

#include "Property.h"

#include <iostream>

using namespace std;

Property::Property(string l, int in){
    i = in;
    type = INT;
    label = l;
}

Property::Property(string l, float in){
    f = in;
    type = FLOAT;
    label = l;
}

Property::Property(string l, bool in){
    b = in;
    type = BOOL;
    label = l;
}

Property::Property(string l, string in){
    new (&s) string(in);
    type = STRING;
    label = l;
}

string Property::get_label(){
    return label;
}

Property::Tag Property::get_type() {
    return type;
}

string Property::to_string() {
    switch(type) {
        case INT:
        return std::to_string(i);
        break;

        case FLOAT:
        return std::to_string(f);
        break;

        case BOOL:
        return std::to_string(b);
        break;

        case STRING:
        return s;
        break;

        default:
        break;
    }

    return "";
}

//for debugging
int main(){
    Property p1("int", 15);
    Property p2("float", float(5.5));
    Property p3("string", string("hello"));
    Property p4("bool", false);

    cout << p1.to_string() << endl;
    cout << p2.to_string() << endl;
    cout << p3.to_string() << endl;
    cout << p4.to_string() << endl;
}
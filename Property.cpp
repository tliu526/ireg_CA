/*
The implementation of Property (a discriminated union).

(c) 2016 Tony Liu
*/

#include "Property.h"

#include <iostream>

using namespace std;

Property::Property(int in){
    i = in;
    type = INT;
}

Property::Property(float in){
    f = in;
    type = FLOAT;
}

Property::Property(string in){
    new (&s) string(in);
    type = STRING;
}

//for debugging 
int main(){
    Property p1(15);
    Property p2(float(5.5));
    Property p3(string("hello"));

    if(p1.type == Property::INT){
        cout << p1.i << endl;
    }
    if(p2.type == Property::FLOAT){
        cout << p2.f << endl;
    }
    if(p3.type == Property::FLOAT){
        cout << p3.s << endl;
    }
}
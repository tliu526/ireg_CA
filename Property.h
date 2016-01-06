/*
A disjoint union/tagged union for Cell properties.

(c) 2015 Tony Liu.
*/

#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

class Property {
    public:
        typedef enum Tag {
            INT,
            FLOAT,
            STRING
        } Tag;

        Property(){};
        ~Property(){};
        Property(int i);
        Property(float f);
        Property(std::string s);

        //The property type
        Tag type;

        union {
            int i;
            float f;
            std::string s;
        };
};

#endif
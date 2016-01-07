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
            INT = 'I',
            FLOAT = 'F',
            BOOL = 'B',
            STRING = 'S'
        } Tag;

        Property(){};
        ~Property(){};
        Property(std::string label, int i);
        Property(std::string label, float f);
        Property(std::string label, bool b);
//        Property(std::string label, std::string s);

        //TODO make this protected? Is string needed?
        union {
            int i;
            float f;
            bool b;
            //std::string s;
        };

        std::string get_label();
        Tag         get_type();
        std::string to_string();

        void set_bool(bool b);
        void set_int(int i);
        void set_float(float f);

    protected:
        //The property type
        Tag type;
        //The Property label
        std::string label;
};

#endif
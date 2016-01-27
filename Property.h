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

        std::string get_label() const;
        Tag         get_type() const;
        std::string to_string() const;

        void set_bool(bool b);
        void set_int(int i);
        void set_float(float f);

        bool operator==(const Property &p) const;
        bool operator!=(const Property &p) const;

    protected:
        //The property type
        Tag type;
        //The Property label
        std::string label;
};

#endif
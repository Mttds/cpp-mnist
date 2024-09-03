#ifndef __DATA_H
#define __DATA_H

#include <vector>
#include "stdint.h"
#include "stdio.h"

class data {
    std::vector<uint8_t>* feature_vector; // No class at end
    uint8_t label;
    double distance;
    int enum_label; // A -> 1, B -> 2, ...

    /* public methods */
    public:
    data();
    ~data();

    void set_feature_vector(std::vector<uint8_t>*);    
    void append_to_feature_vector(uint8_t);
    void set_label(uint8_t);
    void set_enum_label(int);

    int get_feature_vector_size();
    uint8_t get_label();
    uint8_t get_enum_label();
    void set_distance(double);

    std::vector<uint8_t>* get_feature_vector();
    double get_distance();
};

#endif

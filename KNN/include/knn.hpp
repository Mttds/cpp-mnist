#ifndef __KNN_H
#define __KNN_H

#include "common.hpp"

class knn : public common_data {
    int k;
    std::vector<data*> *neighbors;

    public:
    knn();
    knn(int);
    ~knn();

    void find_knearest(data*);
    void set_k(int);
    int predict();
    double calculate_distance(data*, data*);
    double validate_performance();
    double test_performance();
};

#endif

#include "knn.hpp"
#include <cmath>
#include <limits>
#include <map>
#include "stdint.h"
#include "data_handler.hpp"
#include <iostream>

knn::knn() {}

knn::knn(int val) {
    k = val;
}

knn::~knn() {}

void knn::set_k(int val) {
    k = val;
}

void knn::find_knearest(data *query_point) {
    neighbors = new std::vector<data *>;
    double min = std::numeric_limits<double>::max(); // maximum value for a double
    double previous_min = min;
    int index;

    for(int i = 0; i < knn::k; i++) {
        if(i == 0) {
            for(int j = 0; j < training_data->size(); j++) {
                double distance = calculate_distance(query_point, training_data->at(j));
                training_data->at(j)->set_distance(distance);
                if(distance < min) {
                    min = distance;
                    index = j;
                }
            }

            neighbors->push_back(training_data->at(index));
            previous_min = min;
            min = std::numeric_limits<double>::max();
        } else {
            for(int j = 0; j < training_data->size(); j++) {
                double distance = training_data->at(j)->get_distance();
                if(distance > previous_min && distance < min) {
                    min = distance;
                    index = j;
                }
            }

            neighbors->push_back(training_data->at(index));
            previous_min = min;
            min = std::numeric_limits<double>::max();
        }
    }
}

double knn::calculate_distance(data* query_point, data* input) {
    double distance = 0.0;

    if (query_point->get_feature_vector_size() != input->get_feature_vector_size()) {
        printf("Vector size mismatch.\n");
        exit(1);
    }
#ifdef EUCLID
    for (unsigned i = 0; i < query_point->get_feature_vector_size(); i++) {
        distance += pow(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i), 2);
    }

    distance = sqrt(distance);
#elif defined MANHATTAN
    // MANHATTAN GEOMETRY
    for (unsigned i = 0; i < query_point->get_feature_vector_size(); i++) {
        distance += abs(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i));
    }
#endif
    return distance;
}

int knn::predict() {
    std::map<uint8_t, int> class_freq;
    for (int i = 0; i < neighbors->size(); i++) {
        if (class_freq.find(neighbors->at(i)->get_label()) == class_freq.end()) {
            class_freq[neighbors->at(i)->get_label()] = 1;
        } else {
            class_freq[neighbors->at(i)->get_label()]++;
        }
    }

    int best = 0;
    int max  = 0;

    for (auto kv : class_freq) {
        if (kv.second > max) { // if the value is greater than the max
            max = kv.second;
            best = kv.first; // the label (key)
        }
    }

    delete neighbors;
    return best;
}

double knn::validate_performance() {
    double current_performance = 0;
    int count = 0;
    int data_index = 0;

    for (data *query_point : *validation_data) {
        find_knearest(query_point);
        int prediction = predict();

        printf("Prediction = %d -> Query Point = %d - ", prediction, query_point->get_label());

        if (prediction == query_point->get_label()) {
            count++;
        }

        data_index++;
        printf("Current Performance: %.3f %%\n", ((double) count)*100.0 / ((double) data_index));
    }

    current_performance = ((double) count)*100.0/((double) validation_data->size());
    printf("Validation Performance for K = %d: %.3f\n", k, current_performance);
    return current_performance;
}

double knn::test_performance() {
    double current_performance = 0;
    int count = 0;

    for (data *query_point : *test_data) {
        find_knearest(query_point);
        int prediction = predict();
        if (prediction == query_point->get_label())  {
            count++;
        }
    }

    current_performance = ((double) count)*100.0/((double) test_data->size());
    printf("Validation Performance for K = %d: %.3f\n", k, current_performance);
    return current_performance;
}

int main() {
    data_handler *dh = new data_handler();
    dh->read_feature_vector("../data/train-images-idx3-ubyte");
    dh->read_feature_label("../data/train-labels-idx1-ubyte");
    dh->count_classes();
    dh->split_data();

    knn *nearest = new knn();
    nearest->set_k(3);
    nearest->set_training_data(dh->get_training_data());
    nearest->set_test_data(dh->get_test_data());
    nearest->set_validation_data(dh->get_validation_data());
    double performance = 0;
    double best_performance = 0;
    int best_k = 1;

    std::cout << std::endl;

    for(int k = 1; k <= 3; k++) {
        printf("=== Testing with K = %d ===\n", k);
        if(k == 1) {
            nearest->set_k(k);
            performance = nearest->validate_performance();
            best_performance = performance;
        } else  {
            nearest->set_k(k);
            performance = nearest->validate_performance();

            if(performance > best_performance) {
                best_performance = performance;
                best_k = k;
            }
        }
    }

    nearest->set_k(best_k);
    nearest->test_performance();
}

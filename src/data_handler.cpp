#include "data_handler.hpp"

data_handler::data_handler() {
    data_array = new std::vector<data*>;
    test_data = new std::vector<data*>;
    training_data = new std::vector<data*>;
    validation_data = new std::vector<data*>;
}

data_handler::~data_handler() {
    // free dynamically allocated data
}

void data_handler::read_feature_vector(std::string path) {
    uint32_t header[4]; // MAGIC NUM|NUM IMAGES|ROWSIZE|COLSIZE
    unsigned char bytes[4];

    FILE *f = fopen(path.c_str(), "r");

    if (f) {
        for (int i = 0; i < 4; i++) {
            if (fread(bytes, sizeof(bytes), 1, f)) {
                header[i] = data_handler::convert_to_little_endian(bytes);
            }
        }

        printf("Done getting input file header.\n");
        int image_size = header[2] * header[3]; // rowsize * colsize

        // for each image
        for (int i = 0; i < header[1]; i++) {
            data *d = new data();
            uint8_t element[1];

            for (int j = 0; j < image_size; j++) {
                if (fread(element, sizeof(element), 1, f)) {
                    d->append_to_feature_vector(element[0]);
                } else {
                    printf("Error reading from file.\n");
                    exit(1);
                }
            }

            data_array->push_back(d);
        }

        printf("Successfully read and stored %lu feature vectors.\n", data_array->size());
    } else {
        printf("Could not find file.\n");
        exit(1);
    }
}

void data_handler::read_feature_label(std::string path) {
    uint32_t header[2]; // MAGIC NUM|NUM IMAGES
    unsigned char bytes[4];

    FILE *f = fopen(path.c_str(), "r");

    if (f) {
        for (int i = 0; i < 2; i++) {
            if (fread(bytes, sizeof(bytes), 1, f)) {
                header[i] = data_handler::convert_to_little_endian(bytes);
            }
        }

        printf("Done getting label file header.\n");

        // for each label (values can be 0 to 9)
        for (int i = 0; i < header[1]; i++) {
            uint8_t element[1];

            if (fread(element, sizeof(element), 1, f)) {
                data_array->at(i)->set_label(element[0]);
            } else {
                printf("Error reading from file.\n");
                exit(1);
            }
        }

        printf("Successfully read and stored labels.\n");
    } else {
        printf("Could not find file.\n");
        exit(1);
    }
}

void data_handler::split_data() {
    std::unordered_set<int> used_indexes;
    int train_size = data_array->size() * data_handler::TRAIN_SET_PERCENT;
    int test_size = data_array->size() * data_handler::TEST_SET_PERCENNT;
    int validation_size = data_array->size() * data_handler::VALIDATION_SET_PERCENT;

    // training data
    int count = 0;
    while(count < train_size) {
        int rand_index = rand() % data_array->size(); // num between 0 and data_array->size() -1
        if (used_indexes.find(rand_index) == used_indexes.end()) {
            // if the iterator is at the end it didnt find the value
            // so we can use it
            training_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index); // we can no longer use it after this
            count++;
        }
    }

    // test data
    count = 0;
    while(count < test_size) {
        int rand_index = rand() % data_array->size(); // num between 0 and data_array->size() -1
        if (used_indexes.find(rand_index) == used_indexes.end()) {
            // if the iterator is at the end it didnt find the value
            // so we can use it
            test_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index); // we can no longer use it after this
            count++;
        }
    }

    // validation data
    count = 0;
    while(count < validation_size) {
        int rand_index = rand() % data_array->size(); // num between 0 and data_array->size() -1
        if (used_indexes.find(rand_index) == used_indexes.end()) {
            // if the iterator is at the end it didnt find the value
            // so we can use it
            validation_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index); // we can no longer use it after this
            count++;
        }
    }

    printf("Training Data Size: %lu.\n", training_data->size());
    printf("Test Data Size: %lu.\n", test_data->size());
    printf("Validation Data Size: %lu.\n", validation_data->size());
}

void data_handler::count_classes() {
    // store values in our map
    int count = 0;
    for (unsigned i = 0; i < data_array->size(); i++) {
        if (class_map.find(data_array->at(i)->get_label()) == class_map.end()) {
            class_map[data_array->at(i)->get_label()] = count;
            data_array->at(i)->set_enum_label(count);
            count++;
        }
    }

    num_classes = count;
    printf("Successfully extracted %d unique classes.\n", num_classes);
}

uint32_t data_handler::convert_to_little_endian(const unsigned char* bytes) {
    // shift the first byte 24 bits to the left
    // shift the second byte 16 bits to the left
    // shift the third byte 8 bits to the left
    // the fourth byte becomes the first byte
    return (uint32_t) ((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3]));
}

int data_handler::get_class_counts() {
    return num_classes;
}

std::vector<data*> *data_handler::get_training_data() {
    return training_data;
}

std::vector<data*> *data_handler::get_test_data() {
    return test_data;
}

std::vector<data*> *data_handler::get_validation_data() {
    return validation_data;
}

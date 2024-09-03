#include "common.hpp"
#include "data_handler.hpp"
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstring>

void visualize(std::vector<uint8_t> *pixels_vec) {
    // visualize the image as text
    for (int i = 0; i < pixels_vec->size(); i++) {
        uint8_t pixel = pixels_vec->at(i); // Pixel values are 0 to 255. 0 means background (white), 255 means foreground (black).
        printf("Pixel at %d = %d\n", i+1, static_cast<unsigned int>(pixel));
    }
}

int main(int argc, char** argv) {
    data_handler *dh = new data_handler();
    dh->read_feature_vector("../data/train-images-idx3-ubyte");
    dh->read_feature_label("../data/train-labels-idx1-ubyte");
    dh->count_classes();
    dh->split_data();

    char* type = argv[1];
    char* img_num = argv[2];

    std::cout << "Visualizing data set = " << type
              << " and image number " << img_num
              << std::endl;

    if (!strcmp(type,"test") && !strcmp(type,"training") && !strcmp(type,"validation")) {
        std::cout << "The first argument must be [test, training, validation]. Exiting." << std::endl;
        exit(1);
    }

    if (atoi(img_num) < 1 || atoi(img_num) > 784) {
        std::cout << "The second argument must be 1 <= x <= 784 since we have 28x28 pixels. Exiting." << std::endl;
        exit(1);
    }

    std::vector<data*> *data_vec;
    if (strcmp(type,"test")) {
        data_vec = dh->get_test_data();
    } else if (strcmp(type,"validation")) {
        data_vec = dh->get_validation_data();
    } else if (strcmp(type,"training")) {
        data_vec = dh->get_training_data();
    }

    // -1 since if we pass 1 to the cmd line we actually want the
    // first image in the data vector (i.e 0). If we pass 784
    // it won't overflow since we get the 783th element
    data *image_vec = data_vec->at(atoi(img_num) - 1);
    printf(
        "Record %d ==> Feature vector size for digit %d = %d\n",
        atoi(img_num), image_vec->get_label(), image_vec->get_feature_vector_size()
    );
        
    std::vector<uint8_t> *pixel_vec = image_vec->get_feature_vector();
    visualize(pixel_vec);
}

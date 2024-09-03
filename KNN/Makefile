CC=g++
SRC := $(MNIST_CLASSIFIER_ROOT)/KNN/src
CFLAGS_EUCLID := -std=c++11 -DEUCLID
CFLAGS_MANHATTAN := -std=c++11 -DMANHATTAN
INCLUDE_DIR := $(MNIST_CLASSIFIER_ROOT)/KNN/include

all : main

main : $(SRC)/knn.cpp
	$(CC) $(CFLAGS_EUCLID) $(SRC)/knn.cpp -o main -L$(MNIST_CLASSIFIER_ROOT)/lib/ -I$(INCLUDE_DIR) \
	-I$(MNIST_CLASSIFIER_ROOT)/include -ldata

euclid : $(SRC)/knn.cpp
	$(CC) $(CFLAGS_EUCLID) $(SRC)/knn.cpp -o main -L$(MNIST_CLASSIFIER_ROOT)/lib/ -I$(INCLUDE_DIR) \
	-I$(MNIST_CLASSIFIER_ROOT)/include -ldata

manhattan : $(SRC)/knn.cpp
	$(CC) $(CFLAGS_MANHATTAN) $(SRC)/knn.cpp -o main -L$(MNIST_CLASSIFIER_ROOT)/lib/ -I$(INCLUDE_DIR) \
	-I$(MNIST_CLASSIFIER_ROOT)/include -ldata
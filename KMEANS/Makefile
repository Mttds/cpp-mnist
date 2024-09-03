CC=g++
SRC := $(MNIST_CLASSIFIER_ROOT)/KMEANS/src
CFLAGS := -std=c++11
INCLUDE_DIR := $(MNIST_CLASSIFIER_ROOT)/KMEANS/include

all : main

main : $(SRC)/kmeans.cpp
	$(CC) $(CFLAGS) $(SRC)/kmeans.cpp -o main -L$(MNIST_CLASSIFIER_ROOT)/lib/ -I$(INCLUDE_DIR) \
	-I$(MNIST_CLASSIFIER_ROOT)/include -ldata

CC=g++
SRC := $(MNIST_CLASSIFIER_ROOT)/VISUALIZER/src

all : main

main : $(SRC)/visualizer.cpp
	$(CC) $(SRC)/visualizer.cpp -o main -L$(MNIST_CLASSIFIER_ROOT)/lib/ \
	-I$(MNIST_CLASSIFIER_ROOT)/include -ldata

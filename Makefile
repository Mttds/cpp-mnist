CC=g++
INCLUDE_DIR := $(MNIST_CLASSIFIER_ROOT)/include
SRC := $(MNIST_CLASSIFIER_ROOT)/src
CFLAGS := -shared -std=c++11 -g
LIB_DATA := libdata.so

all : $(LIB_DATA)

$(LIB_DATA) : libdir objdir obj/data_handler.o obj/data.o obj/common.o
	$(CC) $(CFLAGS) -o $(MNIST_CLASSIFIER_ROOT)/lib/$(LIB_DATA) obj/*.o

libdir :
	mkdir -p $(MNIST_CLASSIFIER_ROOT)/lib

objdir :
	mkdir -p $(MNIST_CLASSIFIER_ROOT)/obj

obj/data_handler.o : $(SRC)/data_handler.cpp
	$(CC) -fPIC $(CFLAGS) -o obj/data_handler.o -I$(INCLUDE_DIR) -c $(SRC)/data_handler.cpp

obj/data.o : $(SRC)/data.cpp
	$(CC) -fPIC $(CFLAGS) -o obj/data.o -I$(INCLUDE_DIR) -c $(SRC)/data.cpp

obj/common.o : $(SRC)/common.cpp
	$(CC) -fPIC $(CFLAGS) -o obj/common.o -I$(INCLUDE_DIR) -c $(SRC)/common.cpp


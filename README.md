# MNIST_classifier

http://yann.lecun.com/exdb/mnist/

# VS Code environment

- c_cpp_properties.json
```
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "${workspaceFolder}/MNIST_classifier/include"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c17",
            "cppStandard": "gnu++14",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```


# COMPILE
From the root dir: `g++ -std=c++11 -I./include/ -o main ./src/*`

Or use the make file: `./make.sh` or `./make.sh <target>`, where target is one of the available targets in the Makefile

Define MNIST_CLASSIFIER_ROOT in make.sh to be where the project root is in the system.

This will compile the library shared object in ./lib/libdata.so which is used by the other parts of the project.

To run KNN: `cd KNN && ./make.sh && ./main`
To run KMEANS: `cd KMEANS && ./make.sh && ./main`

# ADD libdata.so to the library path

From the project root:

`cd ./lib && export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)`

# FILE FORMATS FOR THE MNIST DATABASE
The data is stored in a very simple file format designed for storing vectors and multidimensional matrices. General info on this format is given at the end of this page, but you don't need to read that to use the data files.
All the integers in the files are stored in the MSB first (high endian) format used by most non-Intel processors. Users of Intel processors and other low-endian machines must flip the bytes of the header.

There are 4 files:

train-images-idx3-ubyte: training set images
train-labels-idx1-ubyte: training set labels
t10k-images-idx3-ubyte : test set images
t10k-labels-idx1-ubyte : test set labels

The training set contains 60000 examples, and the test set 10000 examples.

The first 5000 examples of the test set are taken from the original NIST training set. The last 5000 are taken from the original NIST test set. The first 5000 are cleaner and easier than the last 5000.

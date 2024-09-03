#!/usr/bin/env bash
export MNIST_CLASSIFIER_ROOT=$HOME/software-dev/cpp/MNIST_classifier

echo ===== Executing make for KNN... =====

if [[ ! -z $1 ]]; then
    echo "Target: $1"
    make "$1"
else
    make
fi

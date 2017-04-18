#!/bin/bash

make sparse
for i in {1..3}
do
    echo "Running time $i"
    echo
    echo
    /usr/bin/time -v ./main.out
done

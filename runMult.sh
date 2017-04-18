#!/bin/bash

make
for i in {1..3}
do
    echo "Running time $i"
    echo
    echo
    /usr/bin/time -v ./main.out
done

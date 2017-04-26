#!/bin/bash


make clean
make 
#Loop through a 3 bit system to a 13 bit system

#script denseGrover.txt
for N in {12..12}
do
    
    for i in {1..3}
    do
	echo "Running time $i"
	echo
	echo
	/usr/bin/time -v ./main.out $N
    done
done

make clean
make sparse
#Loop through a 3 bit system to a 13 bit system

#script denseGrover.txt
for N in {16..18}
do
    
    for i in {1..3}
    do
	echo "Running time $i"
	echo
	echo
	/usr/bin/time -v ./main.out $N
    done
done

#exit

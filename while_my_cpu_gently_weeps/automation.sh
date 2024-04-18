#!/bin/bash

clear

count=10

	echo "-----------------------------------------------------------------------------------------"

	g++ -std=c++2a -O3 oldMain.cc
        echo "RUNNING OLD PROGRAM $count TIMES WITH -O3"
for i in $(seq $count); do
	echo "Test: $i"
	./a.out < test | grep -E "Time Elapsed:"
done

	echo "-----------------------------------------------------------------------------------------"

	export OMP_NUM_THREADS=16
	g++ -std=c++2a -fopenmp -O3 OMPmain.cc
        echo "RUNNING PROGRAM $count TIMES WITH OMP MAGIC AND OMP_NUM_THREADS=16"
for i in $(seq $count); do
	echo "Test: $i"
	./a.out < test | grep -E "Time Elapsed:"
done
	echo "-----------------------------------------------------------------------------------------"

	g++ -std=c++2a -fopenmp -pthread -O3 main.cc
        echo "RUNNING PROGRAM $count TIMES WITH 16 THREADS"
for i in $(seq $count); do
	echo "Test: $i"
	./a.out < test2 | grep -E "Time Elapsed:"
done
	echo "-----------------------------------------------------------------------------------------"

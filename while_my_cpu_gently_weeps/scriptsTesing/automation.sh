#!/bin/bash

clear

count=10

#g++ -std=c++2a main.cc
#echo "-----------------------------------------------------------------------------------------"
 #       echo "RUNNING PROGRAM $count TIMES WITH NO OPTIMIZER"
#for i in $(seq $count); do
  #      echo "Test: $i"
 #       ./a.out < test | grep -E "Time Elapsed:"
#done
	echo "-----------------------------------------------------------------------------------------"

	g++ -std=c++2a -O3 main.cc
        echo "RUNNING PROGRAM $count TIMES WITH -O3"
for i in $(seq $count); do
	echo "Test: $i"
	./a.out < test | grep -E "Time Elapsed:"
done

	echo "-----------------------------------------------------------------------------------------"

	g++ -std=c++2a -O3 -fprofile-generate main.cc
for i in $(seq $count); do
	./a.out < test >& /dev/null
done
	
	g++ -std=c++2a -O3 -fprofile-use main.cc
        echo "RUNNING PROGRAM $count TIMES WITH PGO"
for i in $(seq $count); do
	echo "Test: $i"
	./a.out < test | grep -E "Time Elapsed:"
done
	echo "-----------------------------------------------------------------------------------------"

	export OMP_NUM_THREADS=16
	g++ -std=c++2a -fopenmp -O3 OMPmain.cc
        echo "RUNNING PROGRAM $count TIMES WITH OMP MAGIC"
for i in $(seq $count); do
	echo "Test: $i"
	./a.out < test | grep -E "Time Elapsed:"
done
	echo "-----------------------------------------------------------------------------------------"


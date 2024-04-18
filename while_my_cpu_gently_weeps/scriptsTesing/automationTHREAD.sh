#!/bin/bash

clear

count=10

echo "-----------------------------------------------------------------------------------------"

g++ -std=c++2a -O3 -o main main.cc
echo "RUNNING PROGRAM $count TIMES WITH -O3"
for i in $(seq $count); do
echo "Test: $i"
./a.out < test3 | grep -E "Time Elapsed:"
done

echo "-----------------------------------------------------------------------------------------"
export OMP_NUM_THREADS=16
g++ -std=c++2a -fopenmp -O3 -o OMPmain OMPmain.cc
echo "RUNNING PROGRAM $count TIMES WITH OMP MAGIC"
for i in $(seq $count); do
echo "Test: $i"
./a.out < test3 | grep -E "Time Elapsed:"
done
echo "-----------------------------------------------------------------------------------------"


g++ -std=c++2a -O3 -fopenmp -pthread -o THREADmain THREADmain.cc
echo "RUNNING PROGRAM $count TIMES WITH THREAD MAGIC"
for i in $(seq $count); do
echo "Test: $i"
./a.out < test4 | grep -E "Time Elapsed:"
done
echo "-----------------------------------------------------------------------------------------"


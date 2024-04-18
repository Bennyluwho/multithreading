#!/bin/bash

clear

count=10

echo "-----------------------------------------------------------------------------------------"
g++ -std=c++2a -O3 -fopenmp -pthread main.cc
echo "RUNNING THREADS PROGRAM $count TIMES WITH 16 THREADS"
for i in $(seq $count); do
echo "Test: $i"
./a.out < test2 | grep -E "Time Elapsed:"
done
echo "-----------------------------------------------------------------------------------------"


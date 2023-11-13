#!/bin/bash

n=10
for ((i=1; i<=$n; i++)); do
    ./gen > in.txt
    ./EE < in.txt > out.txt
    ./E < in.txt > out2.txt
    diff out.txt out2.txt || { echo "breaking"; break; }
done
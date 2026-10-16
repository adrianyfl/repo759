#!/usr/bin/env zsh

#SBATCH -p instruction 
#SBATCH -J task3
#SBATCH -o task3.out 
#SBATCH -e task3.err 
#SBATCH -c 20
#SBATCH --mem=16G

g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

for s in {1..10}
do
	echo "ts = 2 ^ $s"
	./task3 1000000 8 $((2 ** s))
done

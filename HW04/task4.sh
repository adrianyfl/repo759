#!/usr/bin/env zsh

#SBATCH -p instruction 
#SBATCH -J task4
#SBATCH -o task4.out 
#SBATCH -e task4.err 
#SBATCH -c 8
#SBATCH --mem=16G

g++ task3.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

for t in {1..8}
do
	echo "t = $t"
	./task3 200 200 $t 
done

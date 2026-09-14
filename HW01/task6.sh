#!/usr/bin/env zsh

#SBATCH -p instruction -J task6 -o task6.out -e task6.err -c 2

./task6 6

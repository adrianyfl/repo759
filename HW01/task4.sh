#!/usr/bin/env zsh

#SBATCH -p instruction -J FirstSlurm -o FirstSlurm.out -e FirstSlurm.err -c 2

hostname

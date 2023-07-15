#!/bin/bash
#PBS -l ncpus=9
#PBS -l nodes=3:ppn=3
cd $PBS_O_WORKDIR
hostname
mpiexec -np 9 ./hello

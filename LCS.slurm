#!/bin/bash
#SBATCH --job-name=LCS_Open2
#SBATCH --output slurm5.out
#SBATCH --error slurm5.err
#SBATCH --partition=batch
#SBATCH --qos=short
#SBATCH --constraint=hpcf2013
#SBATCH --exclusive
#SBATCH --cpus-per-task=8

export KMP_AFFINITY="verbose,compact"
export OMP_NUM_THREADS=8
srun ./LCS_Open2 test50000A.txt test50000B.txt 8

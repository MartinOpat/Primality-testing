#!/bin/bash

cd build

if [ ! -f ./PrimalityTesting ]; then
  echo "Executable not found, did you make a build?"
else
  echo "Executable successfully found!"
fi

declare -a tests=(0 1 2)

# Create file name for the given test
BASE_LOGFILE="bench.txt"
counter=0
LOGFILE="${BASE_LOGFILE%.txt}$counter.txt"
while [[ -f $LOGFILE ]]; do
  let counter+=1
  LOGFILE="${BASE_LOGFILE%.txt}$counter.txt"
done
echo "Logging to $LOGFILE"

reps=1
for i in "${tests[@]}"; do
  for j in $(seq 1 $reps); do
    ./PrimalityTesting $i >> $LOGFILE
  done
done

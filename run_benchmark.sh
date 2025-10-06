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

reps=10
for i in "${tests[@]}"; do
  for j in $(seq 1 $reps); do
    # run the program, save its PID, redirect its output into tee
    ./PrimalityTesting "$i" > >(tee -a $LOGFILE) 2>&1 &
    pid=$!

    sleep 10

    if kill -0 "$pid" 2>/dev/null; then
      kill -SIGINT "$pid"
    fi

    wait "$pid" 2>/dev/null
  done
done

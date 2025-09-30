#!/bin/bash

cd build

if [ ! -f ./PrimalityTesting ]; then
  echo "Executable not found, did you make a build?"
else
  echo "Executable successfully found!"
fi

declare -a tests=(0 1 2)

# SIGINT is kill -2
echo "Test log" >test.txt
for i in "${tests[@]}"; do
  ./PrimalityTesting $i | tee -a test.txt &
  pid=$! # save process ID

  sleep 3
  if kill -0 $pid 2>/dev/null; then
    kill -SIGINT $pid
  fi
done

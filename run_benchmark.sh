#!/bin/bash

cd build

if [ ! -f ./PrimalityTesting ]; then
  echo "Executable not found, did you make a build?"
else
  echo "Executable successfully found!"
fi

declare -a tests=(0 1 2)

echo "test" >test.txt
for i in "${tests[@]}"; do
  # run the program, save its PID, redirect its output into tee
  ./PrimalityTesting "$i" > >(tee -a test.txt) 2>&1 &
  pid=$!

  sleep 3

  if kill -0 "$pid" 2>/dev/null; then
    kill -SIGINT "$pid"
  fi

  wait "$pid" 2>/dev/null
done

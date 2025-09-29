cmake_minimum_required(VERSION 3.10)

# Project name
project(PrimalityTesting)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS_DEBUG "-g")

# Add source files
set(SOURCES
    src/main.cpp
    src/trialDivision/trial.cpp
    src/millerRabin/millerRabin.cpp
)

# Include directories
include_directories(
    src
)

# Add executable
add_executable(PrimalityTesting ${SOURCES})

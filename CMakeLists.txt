cmake_minimum_required(VERSION 3.10)

# Project name
project(PrimalityTesting)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_BUILD_TYPE Release)

# Add source files
set(SOURCES
    src/main.cpp
    src/trialDivision/trial.cpp
    src/millerRabin/millerRabin.cpp
    src/bailliePsw/bailliePsw.cpp
)

# Include directories
include_directories(
    src
)

# Add executable
add_executable(PrimalityTesting ${SOURCES})

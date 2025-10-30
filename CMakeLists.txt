cmake_minimum_required(VERSION 3.16)

project(PrimalityTesting)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# SET(CMAKE_C_FLAGS_DEBUG "-O0")
# set(SET(CMAKE_CXX_FLAGS_DEBUG "-O0"))

add_executable(PrimalityTesting
    src/main.cpp
    src/trialDivision/trial.cpp
    src/millerRabin/millerRabin.cpp
    src/bailliePsw/bailliePsw.cpp
)
set_property(TARGET PrimalityTesting PROPERTY UNITY_BUILD ON)
target_include_directories(PrimalityTesting PRIVATE src)


cmake_minimum_required(VERSION 3.23)
project(Lista6TEP)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(Lista6TEP
        CGeneticAlgorithm.cpp
        CGeneticAlgorithm.h
        CIndividual.cpp
        CIndividual.h
        CKnapsackProblem.cpp
        CKnapsackProblem.h
        main.cpp)

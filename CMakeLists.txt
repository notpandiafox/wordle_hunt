cmake_minimum_required(VERSION 3.28)
project(wordle_finder)

set(CMAKE_CXX_STANDARD 26)

add_library(wordle_finder STATIC wordle_hunt.cpp
        wordle_search.h
        "collection_of_nodes.h"
)

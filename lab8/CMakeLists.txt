cmake_minimum_required(VERSION 3.29)
project(lab8)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab8 main.cpp
        UnionFind.h
        Graph.h
        DynamicTable.h
        Helpers.h
)

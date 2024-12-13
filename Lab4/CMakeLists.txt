cmake_minimum_required(VERSION 3.29)
project(Lab4)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab4 main.cpp
        RedBlackTree.h
        private_methods.h
        public_methods.h)

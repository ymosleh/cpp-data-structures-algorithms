cmake_minimum_required(VERSION 3.15)
project(CPP_DSA)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Build the linked list demo
add_executable(linked_list_demo examples/linked_list_demo.cpp)
# C++ Data Structures and Algorithms

A learning-focused implementation of data structures and algorithms using modern C++ features such as smart pointers.
The purpose of this project is to build a deeper understanding of core data structures and demonstrate how they can be used to solve common programming problems.

## Project Structure

```
cpp-data-structures-algorithms/
├── include/
│   ├── data_structures/
│   │   └── linked_list.hpp    # Singly linked list with smart pointers
│   └── algorithms/
│       └── test_utils.hpp     # Utility functions for testing
├── examples/
│   └── linked_list_demo.cpp   # Demonstration of linked list operations
├── tests/                     # Future unit tests
├── docs/                      # Documentation
├── CMakeLists.txt             # Cross-platform build configuration
└── README.md
```

## Building the Project

### Using CMake (Recommended)
```bash
mkdir build
cd build
cmake ..
make
./linked_list_demo
```

### Using Visual Studio
Open `CPP-DSA/CPP-DSA.sln` in Visual Studio and build.

## Currently Implemented

### Data Structures
- **Singly Linked List** (`include/data_structures/linked_list.hpp`)
  - Template-based implementation using `std::unique_ptr`
  - O(1) append and prepend operations
  - Standard operations: insert, remove, get, set
  - Memory-safe with automatic cleanup

### Algorithms
- **Linked List Algorithms**
  - Reverse list in-place
  - Reverse subset of list between positions
  - Find middle node (slow/fast pointer technique)
  - Find kth node from end
  - Remove duplicates from sorted list
  - Binary to decimal conversion
  - List partitioning
  - Swap nodes in Pairs
  - Cycle detection (in test utilities)

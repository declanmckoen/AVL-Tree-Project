# AVL Tree Project
This project provides an implementation of the AVL tree data structure in C++, ensuring efficient insertion, deletion, and retrieval operations for managing any kind of data type. The AVL tree is a self-balancing binary search tree, where the difference in heights between left and right subtrees is at most one for all nodes, maintaining O(log n) time complexity for these operations.

# Features

Insertion: Efficiently insert elements into the AVL tree while maintaining its balanced property.
Deletion: Remove elements from the AVL tree, ensuring the tree remains balanced.
Retrieval: Quickly retrieve elements from the AVL tree.
Comprehensive Testing: Integrated unit tests using the Catch2 framework to ensure the accuracy and performance of AVL tree operations.

# Repository Organization

The project contains the following files:
AVL.h: Header file containing the declaration of the AVL tree class and its member functions.
AVL.cpp: Implementation file defining the member functions of the AVL tree class.
main.cpp: Contains the abstracted user interface to interact with the AVL tree.

# Run Locally

To compile and run this project, you will need:
A C++ compiler that supports C++11 or later.
Catch2 framework for running unit tests.


Clone the repository:
git clone https://github.com/declanmckoen/AVL-Tree-Project.git
cd AVL-Tree-Project


Compile the source files:
g++ -std=c++11 -o avl_tree main.cpp AVL.cpp


Execute the compiled program:
./avl_tree


The main.cpp file provides a simple user interface to interact with the AVL tree. You can modify this file to suit your needs or to add more functionality.

# Contributions

Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

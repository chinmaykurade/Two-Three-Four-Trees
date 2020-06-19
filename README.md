# Two-Three-Four-Trees

Two-three-four trees (also known as Two-four trees and hereby referenced as 2-3-4 trees) is a self balancing data structure. It can be considered as a generalisation of the AVL tree.

### General Rules for implementing a 2-3-4 tree

#### 1. Each internal node must have atleast 1 and atmost 3 data elements

#### 2. Each data element has a left child and a right child. Hence, each internal node must have minimum 2 and maximum 4 children, hence the name 2-3-4 trees

#### 3. Any sub-trees of a particular node must have same depth(or height)

This repository includes files to insert or delete a particular data element from a 2-3-4 tree and also traversing and searching a particular element.

Code for insertion, searching(with predecessor) and deletion is located in tf_insertion.cpp, tf_search.cpp and tf_deletion.cpp respectively.
tf_utils.cpp contains the utilities to take input from the user.

##### Please open 'two_four_trees.cbp' in Code::Blocks and run main.cpp to execute the program.

Else run main.exe if not able to.

After running, you can choose to create tree with given input elements or with random elements. Max random elements are limited to 30,000.

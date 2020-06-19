#ifndef TWO_FOUR_H_INCLUDED
#define TWO_FOUR_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*  DSA Assignment- 2-3-4 trees
*
*   Submitted by            :Chinmay Kurade (2017UME0100)
*   Author                  :Chinmay Kurade
*   Date                    :21 May, 2020
*
*   Description:
/*   This file defines the node class, search_result class and the two-four tree
*   (tf_tree) class, with all the functions.
*   Each node of the tree consists of:
*   1. A key array of 4 elements. The extra element is needed to insert a value
*      when there are already three elements (overflow is handled by splitting).
*   2. A counter(countt) that stores the number of elements in the particular node
*   3. A pointer array of 5 elements. pointer[0] points to leftmost child and
*      pointer[3] to rightmost child. However, they point to NULL if no child is
*      present. Again, extra pointer needed for same reason as that of key.
*   4. A pointer(parent) that points to the parent of the particular node.
*/

/*****************************************************************************/

class node{
public:
    int key[4]={-1,-1,-1,-1};
    int countt=0;
    node* pointer[5] = {NULL,NULL,NULL,NULL,NULL};
    node* parent = NULL;
};

// This is a class to return the search result- node address(position) and index
// of a particular value in the tree.
class search_result{
public:
    int index=-1;
    node* position=NULL;
};

class tf_tree{
private:
    node* root;

public:
    tf_tree(int n);

    tf_tree();

    void update_root(node* new_root);

    bool insert_value(int n);

    bool insert_root(node* current_node,int n);

    int print_inorder_root(node* root);

    int print_inorder();

    void print();

    node* get_root();

    void handle_overflow(node* current_node);

    void add_to_parent(int middle,node* new_node);

    int get_levels(node* current_node);

    void add_val(node* current_node,int n);

    search_result* search_value(int value);

    bool delete_value(int value);

    search_result* predecessor(int value);

    void replace_value(int delete_val,int add_val);

    search_result* parent_to_rotate(node* current_node);

    void rotate_sibling(node* current_node,search_result* parent_result);

    node* handle_underflow(node* current_node);

    int count_elements();

    int count_root(node* current_root);

};

void print_node(node* current_node);

node* search_node(int value,node* root);

search_result* search_lt(int value,node* current_root);

search_result* get_max(node* current_root);

int get_index(int value, node* current_root);

void shift_left(node* current_node,int start);

void shift_right(node* current_node,int upto);

void merge_right(node* current_node,int same);

void merge_left(node* current_node,int same);

vector<int> str2num(string str);

void print_nums(vector<int> nums);

node* insert_array(tf_tree my_tree,vector<int> nums);

node* delete_array(tf_tree my_tree,vector<int> nums);

void run_input();

void run_random();

#endif // TWO_FOUR_H_INCLUDED

/*****************************************************************************/

#include <iostream>
#include <string>
#include "two_four.h"
using namespace std;

/*  DSA Assignment- 2-3-4 trees
*
*   Submitted by            :Chinmay Kurade (2017UME0100)
*   Author                  :Chinmay Kurade
*   Date                    :21 May, 2020
*
*   Description:
/*  This file contains code to print the elements in the tree and also to
*   count the number of elements and number of levels.
*/

/*****************************************************************************/

node* tf_tree::get_root(){
    return root;
}


// Function to print a particular branch of the tree after a node by inorder
// traversal. It returns number of elements in that branch.
int tf_tree::print_inorder_root(node* current_root){
    int num=0;
    if(current_root->pointer[0]==NULL){
        print_node(current_root);
        return current_root->countt;
    }
    else{
        num += print_inorder_root(current_root->pointer[0]);
        cout << current_root->key[0] << endl;
        num += print_inorder_root(current_root->pointer[1])+1;
        if(current_root->countt>1){
            cout << current_root->key[1] << endl;
            num += print_inorder_root(current_root->pointer[2])+1;
        }
        if(current_root->countt>2){
            cout << current_root->key[2] << endl;
            num += print_inorder_root(current_root->pointer[3])+1;
        }
    }
    return num;
}


// Function to print the entire tree inorder.
int tf_tree::print_inorder(){
    return print_inorder_root(root);
}

// Function to count the number of elements in the tree branch recursively
int tf_tree::count_root(node* current_root){
    int temp=0;
    if(current_root->pointer[0]==NULL) return current_root->countt;
    for(int i=0;i<=current_root->countt;i++){
        temp+=count_root(current_root->pointer[i])+1;
    }
    temp-=1;
    return temp;
}

int tf_tree::count_elements(){
    return count_root(root);
}


void print_node(node* current_node){
    for(int i=0;i<current_node->countt;i++){
        cout << current_node->key[i] << endl;
    }
}


// To get the number of levels in the tree recursively.
int tf_tree::get_levels(node* current_node){
    if(current_node->pointer[0]== NULL) return 1;
    return get_levels(current_node->pointer[0])+1;
}

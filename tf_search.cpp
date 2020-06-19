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
/*  This file contains functions to search for a particular value in a tree and
*   also to find the predecessor of a particular value.
*/

/*****************************************************************************/

// This function searches for the position(node address) and index of the value
// at that node.
search_result* tf_tree::search_value(int value){
    search_result* result = new search_result;
    if(result==NULL) cout<<"Unable to allocate memory!"<<endl;
    result->position = search_node(value,root);
    if(result->position!=NULL) result->index=get_index(value,result->position);
    return result;
}


// This function searches for a particular value in a particular branch.
// Given a node address, we first search in the node for the value and return
// the node address if the value is present. Else we search in the appropriate
// child branch using recursion.
node* search_node(int value,node* current_root){
    if(current_root==NULL){
        return NULL;
    }
    if(current_root->pointer[0]==NULL){       // If the node is a leaf
        for(int i=0;i<current_root->countt;i++){
            if(current_root->key[i]==value){
                return current_root;
            }
        }
        return NULL;                          // If no value does not match,
    }                                         // return NULL
    for(int j=0;j<current_root->countt;j++){
        if(value<current_root->key[j]){
            return search_node(value,current_root->pointer[j]);
        }
        else if(value==current_root->key[j]){
            return current_root;
        }
    }
    return search_node(value,current_root->pointer[current_root->countt]);
}


// Function to get the index of a value at a particular node
int get_index(int value, node* current_root){
    for(int j=0;j<current_root->countt;j++){
        if(value==current_root->key[j]){
            return j;
        }
    }
    return -1;
}


// To find the predecessor
search_result* tf_tree::predecessor(int value){
    search_result* result = search_value(value);
    node* current_node = result->position;
    int idx = result->index;
    if(current_node==NULL) return NULL;
    if(current_node->pointer[0]==NULL){       // If the node is a leaf(2 cases):
        if(idx==0 && current_node->parent==NULL){// Case1: If it is a root and
            return NULL;                      // the value is smallest, then no
        }                                     // predecessor is present.
        else if(idx==0 && current_node->parent!=NULL){// Case2: If not at,root
            return search_lt(value,current_node->parent);// search for a value
        }                                     // less the the particular value
        result->index = idx-1;                // in the parent node
        result->position = current_node;
        return result;
    }
    else{                                     // If the node is not a leaf, find
        return get_max(current_node->pointer[idx]);// the maximum value in its
    }                                         // left child branch.
}


// To get the maximum element in a particular branch. This is actually the
// rightmost element in that branch. Here it is found using recursion.
search_result* get_max(node* current_root){
    if(current_root->pointer[0]!=NULL){
        return get_max(current_root->pointer[current_root->countt]);
    }
    search_result* result = new search_result;
    result->position = current_root;
    result->index = current_root->countt-1;
    return result;
}


// To find a key smaller than a particular key in the parent.
// If the first element of the parent is greater than that key, we search in
// the parent of the parent. Else we return the address and appropriate index.
search_result* search_lt(int value,node* current_root){
    if(current_root==NULL) return NULL;
    if(value<current_root->key[0]) return search_lt(value,current_root->parent);
    search_result* result = new search_result;
    if(value>current_root->key[0] && current_root->countt==1){
        result->position = current_root;
        result->index = 0;
        return result;
    }
    for(int i=0;i<current_root->countt-1;i++){
        if(current_root->key[i]<value && current_root->key[i+1]>value){
            result->position = current_root;
            result->index = i;
            return result;
            }
        }
    if(current_root->key[current_root->countt-1]<value){
        result->position = current_root;
        result->index = current_root->countt-1;
        return result;
    }
    return NULL;
}

/*****************************************************************************/

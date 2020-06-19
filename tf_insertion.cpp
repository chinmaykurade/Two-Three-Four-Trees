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
/*  This file contains code to add a particular value in the two-four tree.
*   We search for the appropriate position to add the value, using recursion to
*   traverse through the tree. When we find the particular leaf, we insert the
*`  value at appropriate index. Overflow(>3 elements) is handled by splitting.
*/

/*****************************************************************************/

// The Constructor function initializes the root node with one element
// This means that the tree must have at least on element at any time
tf_tree::tf_tree(int n){
    root = new node;
    root->key[0] = n;
    root->countt = 1;
}


void tf_tree::update_root(node* new_root){
    root = new_root;
}


// The following function adds a value at given node address (irrespective of
// node-overflow). It finds the appropriate index to  add at and inserts the
// value at that index, after shifting all values after it.
void tf_tree::add_val(node* current_node,int n){
    int idx=0;
    while(n>current_node->key[idx] && idx!=current_node->countt){
        idx++;
    }
    current_node->countt=current_node->countt+1;
    for(int i=3;i>idx;i--){
        current_node->key[i] = current_node->key[i-1];
    }
    current_node->key[idx] = n;
}


// This function inserts a value in the tree, with a particular node as root.
// This function enables us to insert the value in the tree recursively.
// All the cases(1,2 or 3 elements in leaf) are handled individually for the
// sake of simplicity.
// In case of 1 or 2 elements already present in leaf node, the value is simply
// inserted in the leaf at appropriate index.
// In case of 3 elements present, the value is still inserted, but after
// inserting, the third element is added to the parent node, and the leaf node
// is split into two. If this results in Overflow at parent, it is also handled
// by splitting, and so on.
bool tf_tree::insert_root(node* current_root,int n){
    search_result* result = search_value(n);
    if(result->position!=NULL){
//        cout<<"Entered element "<<n<<" already exists!"<<endl;
        return 0;
    }
    delete(result);
    if(current_root->countt==1){              // For 1 element in node
        if(current_root->pointer[0]==NULL){   // If the node is a leaf
            add_val(current_root,n);          // just add at appropriate index
        }
        else if(current_root->key[0]>n){      // Else insert in the appropriate
            insert_root(current_root->pointer[0],n);  // child branch
        }
        else{
            insert_root(current_root->pointer[1],n);
        }
    }
    else if(current_root->countt==2){         // Same process as above for 2
        if(current_root->pointer[0]==NULL){   // elements in node
            add_val(current_root,n);
        }
        else if(current_root->key[0]>n){
            insert_root(current_root->pointer[0],n);
        }
        else if(current_root->key[0]<n && n<current_root->key[1]){
            insert_root(current_root->pointer[1],n);
        }
        else{
            insert_root(current_root->pointer[2],n);
        }
    }
    else if(current_root->countt==3){         // For 3 elements in node
        if(current_root->pointer[0]==NULL){   // If the node is a leaf, we
            add_val(current_root,n);          // insert the value and handle
            handle_overflow(current_root);    // overflow by splitting
        }
        else if(current_root->key[0]>n){      // Else the process is similar
            insert_root(current_root->pointer[0],n);
        }
        else if(current_root->key[0]<n && n<current_root->key[1]){
            insert_root(current_root->pointer[1],n);
        }
        else if(current_root->key[1]<n && n<current_root->key[2]){
            insert_root(current_root->pointer[2],n);
        }
        else{
            insert_root(current_root->pointer[3],n);
        }
    }
    else if(current_root->countt<1){          // Hopefully you wont see these!
        cout<<"ERROR!! Node Underflow while adding "<<n<<"!!"<<endl;
    }
    else{
        cout<<"ERROR!! Node Overflow while adding "<<n<<"!!"<<endl;
    }
    return 1;
}


// This function inserts a particular value in the tree
bool tf_tree::insert_value(int n){
    return insert_root(root,n);
}


// This function handles overflow at a particular node by splitting it at third
// element and adding the third element to parent.
// If there is no parent, it creates a new node as root with the third element
// Overflow at parent is checked and also handled
void tf_tree::handle_overflow(node* current_node){
    node* new_node = new node;                // We create a new node and assign
    new_node->pointer[0] = current_node->pointer[3];// it the respective pointers
    new_node->pointer[1] = current_node->pointer[4];// of the overflown node.
    if(new_node->pointer[0]!=NULL){           // Also we should update the
        new_node->pointer[0]->parent=new_node;// parent of the respective child
        new_node->pointer[1]->parent=new_node;// nodes to new_node.
    }
    current_node->pointer[3]=NULL;
    current_node->pointer[4]=NULL;
    new_node->key[0] = current_node->key[3]; // Last(fourth) element
    new_node->countt = 1;
    int middle = current_node->key[2];
    current_node->key[2] = -1;
    current_node->key[3] = -1;
    current_node->countt=2;
    if(current_node->parent==NULL){           // If there is no parent, we
        node* new_root = new node;            // create a new root which
        new_root->key[0] = middle;            // contains the third(middle) key
        new_root->pointer[0] = current_node;  // and is parent of the split
        new_root->pointer[1] = new_node;      // nodes.
        current_node->parent = new_root;
        new_node->parent = new_root;
        new_root->countt=1;
        root = new_root;
    }
    else{
        new_node->parent=current_node->parent;// Else we add the middle element
        add_to_parent(middle,new_node);       // to the parent.
        if(current_node->parent->countt==4){  // We also check for overflow at
            handle_overflow(current_node->parent);// parent node and handle it
        }
    }
}


// This function inserts the middle element in the parent node. Also it
// updates the respective child pointer of parent to point to the new node.
void tf_tree::add_to_parent(int middle,node* new_node){
    node* parent_node = new_node->parent;
    int idx=0;
    while(middle>parent_node->key[idx]){
        idx++;
        if(idx==parent_node->countt){
            break;
        }
    }
    parent_node->countt=parent_node->countt+1;
    for(int i=3;i>idx;i--){
        parent_node->key[i] = parent_node->key[i-1];
        parent_node->pointer[i+1] = parent_node->pointer[i];
    }
    parent_node->key[idx] = middle;
    parent_node->pointer[idx+1] = new_node;
}

/*****************************************************************************/

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
/*  This file contains code to delete a particular value from the tree.
*   All the cases are explained along with the code below
*/

/*****************************************************************************/

// To delete a particular element:
bool tf_tree::delete_value(int value){
//    cout<<"P";
    search_result* result = search_value(value);
//    cout<<"Q";
    if(result->position==NULL){
//        cout<<"Cannot delete "<<value<<". No such value found!"<<endl;
//        cout<<"1"<<endl;
        delete(result);
        return 0;
    }
    else if(result->position->pointer[0]==NULL && \
            result->position->parent==NULL && result->position->countt==1){
        cout<<"Cannot delete! Only one element is present in the tree!"<<endl;
        cout<<"Please first enter another element and then delete it"<<endl;
        cout<<"2"<<endl;
        delete(result);
        return 1;
    }
    node* current_node = result->position;
    int idx = result->index;
    delete(result);
    if(current_node->pointer[0]==NULL){     // If the node is a leaf
        for(int i=idx;i<current_node->countt-1;i++){
            current_node->key[i] = current_node->key[i+1];
        }
        current_node->key[current_node->countt-1]=-1;// We delete the value
        current_node->countt-=1;
        if(current_node->countt==0){        // And check for node underflow
            root=handle_underflow(current_node);// and handle it
        }
        return 1;
    }
    else{
        search_result* result_prdcssr = predecessor(value);// Else find the
        node* prdcssr = result_prdcssr->position;// Predecessor and first
        int prdcssr_idx = result_prdcssr->index;
        delete(result_prdcssr);
        int prdcssr_value = prdcssr->key[prdcssr_idx];
        delete_value(prdcssr_value);          // delete the predecessor and then
        replace_value(value,prdcssr_value);   // replace the value to delete
        return 1;                               // with predecessor's value
    }
}


// Underflow means that there is no element in the particular node
// Various cases are described below
node* tf_tree::handle_underflow(node* current_node){
    int same;
    if(current_node->parent==NULL){           // If the node is a root, we
        root=current_node->pointer[0];        // update the root of the tree its
        current_node->pointer[0]->parent=NULL;// the child and
        delete(current_node);                 // delete the previous root node.
        return root;
    }
    search_result* parent = parent_to_rotate(current_node);// parent_to_rotate
    if(parent!=NULL){                         // returns non-NULL if a sibling
        rotate_sibling(current_node,parent);  // with >1 element exists. We
        delete(parent);
        return root;                          // rotate in this case.
    }
    else{                                     // Else if no sibling to rotate,
        for(int i=0;i<=3;i++){                // merge in the respective direction
            if(current_node->parent->pointer[i]==current_node) same=i;
        }
        if(same==0){
            node* sibling = current_node->parent->pointer[1];
            merge_right(current_node,same);
            if(sibling->parent->countt==0) root=handle_underflow(sibling->parent);
        }
        else{
            node* sibling = current_node->parent->pointer[same-1];
            merge_left(current_node,same);
            if(sibling->parent->countt==0) root=handle_underflow(sibling->parent);
        }
        return root;
    }
}


// This function finds whether a sibling with>1 element exists and returns
// the location of the respective parent element to rotate through.
search_result* tf_tree::parent_to_rotate(node* current_node){
    search_result* result = new search_result;
    int prev,next;
    for(int i=0;i<=current_node->parent->countt;i++){
        if(current_node->parent->pointer[i]==current_node){
            prev = i-1;
            next = i+1;
        }
    }
    if(prev>=0){
        if(current_node->parent->pointer[prev]->countt>1){
            result->position =  current_node->parent;
            result->index = prev;
            return result;
        }
    }
    if(next<=current_node->parent->countt){
        if(current_node->parent->pointer[next]->countt>1){
            result->position =  current_node->parent;
            result->index = next-1;
            return result;
        }
    }
    return NULL;
}


// Rotate the sibling through the respective parent element.
void tf_tree::rotate_sibling(node* current_node,search_result* parent_result){
    node* parent = parent_result->position;
    node* child = NULL;
    int idx_p = parent_result->index;
    int sibling_val,parent_val;
    parent_val = parent->key[idx_p];
    if(parent->pointer[idx_p]==current_node){     // Right sibling
        sibling_val = parent->pointer[idx_p+1]->key[0];
        child = parent->pointer[idx_p+1]->pointer[0];
        if(child!=NULL){
            child->parent=current_node;
        }
        current_node->pointer[1]=child;
        parent->pointer[idx_p+1]->pointer[0]=NULL;
        shift_left(parent->pointer[idx_p+1],0);
    }
    else{
        sibling_val = parent->pointer[idx_p]->key[parent->pointer[idx_p]->countt-1];
        child = parent->pointer[idx_p]->pointer[parent->pointer[idx_p]->countt];
        if(child!=NULL){
            child->parent=current_node;
        }
        current_node->pointer[1]=current_node->pointer[0];
        current_node->pointer[0]=child;
        parent->pointer[idx_p]->pointer[parent->pointer[idx_p]->countt]=NULL;
        shift_right(parent->pointer[idx_p],3);
    }
    replace_value(parent_val,sibling_val);
    add_val(current_node,parent_val);
}


// Merge the underflown node with the right sibling
void merge_right(node* current_node,int same){
    node* sibling = current_node->parent->pointer[same+1];
    sibling->pointer[2] = sibling->pointer[1];
    sibling->pointer[1] = sibling->pointer[0];
    sibling->pointer[0] = current_node->pointer[0];
    sibling->key[1] = sibling->key[0];
    sibling->key[0] = sibling->parent->key[same];
    sibling->countt+=1;
    if(current_node->pointer[0]!=NULL){
        current_node->pointer[0]->parent=sibling;
    }
    shift_left(sibling->parent,same);
    delete(current_node);
}


// Merge the underflown node with the left sibling
void merge_left(node* current_node,int same){
    node* sibling = current_node->parent->pointer[same-1];
    sibling->pointer[2] = current_node->pointer[0];
    sibling->key[1] = sibling->parent->key[same-1];
    sibling->countt+=1;
    if(current_node->pointer[0]!=NULL){
        current_node->pointer[0]->parent=sibling;
    }
    sibling->parent->pointer[same] = sibling;
    shift_left(sibling->parent,same-1);
    delete(current_node);
}


// Shift all elements of a node to left, starting from a particular index.
void shift_left(node* current_node,int start){
    for(int i=start;i<current_node->countt;i++){
        current_node->key[i]=current_node->key[i+1];
        current_node->pointer[i]=current_node->pointer[i+1];
    }
    current_node->pointer[current_node->countt]=NULL;
    current_node->countt-=1;
}


// Shift all elements of a node to right, up to a particular index.
void shift_right(node* current_node,int upto){
    for(int i=upto;i>0;i--){
        current_node->key[i] = current_node->key[i-1];
        current_node->pointer[i] = current_node->pointer[i-1];
    }
    shift_left(current_node,0);
}


// Replace a particular value by another
void tf_tree::replace_value(int delete_val,int add_val){
    search_result* result = search_value(delete_val);
    if(result->position==NULL) cout<<"llK";
    result->position->key[result->index] = add_val;
    delete(result);
}

/*****************************************************************************/

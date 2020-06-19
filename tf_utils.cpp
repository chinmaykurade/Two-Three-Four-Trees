#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include "two_four.h"
using namespace std::chrono;
using namespace std;

/*  DSA Assignment- 2-3-4 trees
*
*   Submitted by            :Chinmay Kurade (2017UME0100)
*   Author                  :Chinmay Kurade
*   Date                    :21 May, 2020
*
*   Description:
/*  This file contains the utility functions to take input, process it and
*   display the output
*/

/*****************************************************************************/

// Convert the input string(comma separated) to an array of elements
vector<int> str2num(string str){
    vector<int> nums;
    int temp=0;
    int minuss=0;
    for(int i=0;i<int(str.length());i++){
        if(str[i]==','){
            if(minuss){
                temp*=-1;
                minuss=0;
            }
            nums.push_back(temp);
            temp=0;
        }
        else if(str[i]=='-'){
            minuss = 1;
        }
        else{
            temp=temp*10+(int(str[i])-48);
        }
    }
    if(minuss){
        temp*=-1;
        minuss=0;
    }
    if(str[str.length()-1] != ',') nums.push_back(temp);

    return nums;
}

void print_nums(vector<int> nums){
    cout<<"..........................."<<endl;
    for (int i = 0; i < nums.size(); i++){
        cout<<nums[i]<<endl;
    }
    cout<<"..........................."<<endl;
}


// Insert an array of elements in a tree and return its root address
node* insert_array(tf_tree my_tree,vector<int> nums){
    for (int i = 0; i < nums.size(); i++){
        if(!my_tree.insert_value(nums[i]))
            cout<<"Entered element "<<nums[i]<<" already exists!"<<endl;
    }
    return my_tree.get_root();
}


// Delete an array of elements from a tree and return its root address
node* delete_array(tf_tree my_tree,vector<int> nums){
    for (int i = 0; i < nums.size(); i++){
        if(!my_tree.delete_value(nums[i]))
            cout<<"Cannot delete "<<nums[i]<<". No such value found!"<<endl;
    }
    return my_tree.get_root();
}


// Run the program to take input elements from user and insert or delete them
// from the 2-3-4 tree.
void run_input(){
    int choice,n,num_elements;
    string c;
    vector<int> v;
    cout<<"Enter the first element value to begin the tree with:"<<endl;
    cin>>n;
    tf_tree my_tree(n);

    while(choice!=-1){
        cout<<"Enter 1 to insert, 2 to delete or -1 to exit:"<<endl;
        cin>>choice;
        switch(choice){
        case 1:
            cout<<"Enter the numbers to insert, separated by a comma:"<<endl;
            cout<<"Please enter only integers and do no enter any spaces!"<<endl;
            cin>>c;
            v = str2num(c);
            my_tree.update_root(insert_array(my_tree,v));
        break;
        case 2:
            cout<<"Enter the numbers to delete, separated by a comma:"<<endl;
            cout<<"Please enter only integers and do no enter any spaces!"<<endl;
            cin>>c;
            v = str2num(c);
            my_tree.update_root(delete_array(my_tree,v));
        break;
        }
        cout<<"\n";
        cout<<"\n********************************************************"<<endl;
        cout<<"Elements in the tree in ascending order:"<<endl;
        num_elements = my_tree.print_inorder();
        cout<<"...................................."<<endl;
        cout<<"Number of elements = "<<num_elements<<endl;
        cout<<"...................................."<<endl;
        cout<<"Number of levels = "<<my_tree.get_levels(my_tree.get_root())<<endl;
        cout<<"********************************************************\n"<<endl;
    }
}


void run_random(){
    int num=0,choice=1,choicep=1,countt=0,temp=0;
    int num_ele=0;
    bool val;
    auto tic = high_resolution_clock::now();
    auto toc = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(toc-tic);
    tf_tree my_tree(1);              // We begin with default value of 1 at root
    srand((unsigned)time(0));
    while(choice!=-1){
        cout<<"Enter 1 to insert, 2 to delete, 3 to print or -1 to exit:"<<endl;
        cin>>choice;
        switch(choice){
        case 1:
            num_ele=30001-my_tree.count_elements();
            cout<<"Enter the number of elements(<="<<num_ele<<") to insert:"<<endl;
            cin>>num;
            while(num>num_ele){
                cout<<"Please enter a number less than "<<num_ele<<endl;
                cin>>num;
            }
            countt=0;
            tic = high_resolution_clock::now();
            while(countt<num){
                if(my_tree.insert_value(rand())) countt++;
            }
            toc = high_resolution_clock::now();

            duration = duration_cast<microseconds>(toc-tic);
            num_ele = my_tree.count_elements();
            cout<<"....................................................."<<endl;
            cout<<"Inserted "<<countt<<" unique elements randomly."<<endl;
            cout<<"Time taken = "<<\
            duration.count()<<" microseconds.\nTotal elements in tree = ";
            cout<<num_ele<<endl;
            cout<<"Number of levels = "<<my_tree.get_levels(my_tree.get_root());
            cout<<"\n....................................................."<<endl;
        break;
        case 2:
            num_ele = my_tree.count_elements();
            cout<<"Enter the number of elements(<"<<num_ele<<") to delete:"<<endl;
            cin>>num;
            while(num>num_ele){
                cout<<"Please enter a number less than "<<num_ele<<endl;
                cin>>num;
            }
            countt=0;
            tic = high_resolution_clock::now();
            for(int i=0; i<900000; i++){
                temp = rand();
                val = my_tree.delete_value(temp);
                if(val) countt++;
                if(countt==num) break;
            }
            toc = high_resolution_clock::now();
            duration = duration_cast<microseconds>(toc-tic);
            num_ele = my_tree.count_elements();
            cout<<"....................................................."<<endl;
            cout<<"Deleted "<<countt<<" unique elements randomly."<<endl;
            cout<<"Time taken = "<<\
            duration.count()<<" microseconds.\nTotal elements in tree = ";
            cout<<num_ele<<endl;
            cout<<"Number of levels = "<<my_tree.get_levels(my_tree.get_root());
            cout<<"\n....................................................."<<endl;
        break;
        case 3:
            cout<<"*****************************************************"<<endl;
            cout<<"Elements in the tree in ascending order:\n"<<endl;
            my_tree.print_inorder();
            cout<<"....................................................."<<endl;
            cout<<"Number of elements = "<<num_ele<<endl;
            cout<<"....................................................."<<endl;
            cout<<"Number of levels = "<<my_tree.get_levels(my_tree.get_root());
            cout<<"\n*************************************************\n"<<endl;
        break;

        }
    }
}

//void run_combine()

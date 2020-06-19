#include <iostream>
#include <string>
#include "two_four.h"
using namespace std;

/*  DSA Assignment- 2-3-4 trees
*
*   Submitted by            :Chinmay Kurade (2017UME0100)
*   Author                  :Chinmay Kurade
*   Date                    :21 May, 2020
*/

int main(){
    int choice=1;
    cout<<"Enter 1 to create tree with random elements or 2 to create tree"<<\
    " with given input elements:"<<endl;
    cin>>choice;
    while(choice!=1 && choice!=2){
        cout<<"Invalid option!"<<endl;
        cout<<"Enter 1 to create tree with random elements or 2 to create tree"<<\
        " with given input elements:"<<endl;
        cin>>choice;
    }
    if(choice==2) run_input();
    else run_random();
    return 0;

}

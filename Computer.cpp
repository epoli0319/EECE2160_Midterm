//@file Computer.cpp
//@Author Eleni Polichronakis
//@date October 2020
//@brief This is the .cpp file for the Computer class


#include "Computer.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
using namespace std;

void Computer::TakeTurn() {
    int choice;
    cout<<"\n\nIt's the Computer's turn!!"<<endl;
    cout<<"\nPress 1 to print the Computer's Board, 0 to continue"<<endl;
    cin>>choice;
    if(choice==1){
        printBoard();
    }
    int roll = diceRoll();
    cout<<"The computer rolled a "<<roll<<endl;
    move(roll);
}
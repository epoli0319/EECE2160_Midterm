//@file Person.cpp
//@Author Eleni Polichronakis
//@date October 2020
//@brief This is the .cpp file for the Person class


#include "Person.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
using namespace std;


void Person::TakeTurn() {
    cout<<"\n\n"<<player_name<<" :It's your turn!!"<<endl;
    int choice;
    //Ask to print the printBoard
    cout<<"\nPress 1 to print the Board, 0 to continue"<<endl;
    cin>>choice;
    if(choice==1){
        printBoard();
    }
    //Ask if they want to try a math question
    cout<<"\nPress 1 to try some math, 0 to continue"<<endl;
    cin>>choice;

    if(choice==1){
        int num1= rand()%20+1;
        int num2= rand()%20+1;    
        int sum;
        cout<<"What is "<<num1<<"+"<<num2<<"?";
        cin>>sum;
        if(sum==(num1+num2)){
          cout<<"Double roll!!";
          int roll = diceRoll();
          cout<<"You rolled a "<<roll<<endl;
          move(roll);
        }
    }

    int roll = diceRoll();
    cout<<"You rolled a "<<roll<<endl;
    move(roll);
}

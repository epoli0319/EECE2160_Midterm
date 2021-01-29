//@file Player.cpp
//@Author Eleni Polichronakis
//@date October 2020
//@brief This is the .cpp file for the DE1SoC class


#include "Player.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
using namespace std;


const int Snakes[8]={29,38,47,53,62,86,92,97};
const int Ladders[8]={8,2,20,32,41,74,85,82};

Player::Player(){
    position=1;
    
}

void Player::setPlayerName(string name){
  player_name = name;
}
int Player::getPosition() {
    return position;
}


int Player::diceRoll(){
    return rand()%6+1; //rand% is 0 to 5
}


void Player::printBoard(){
    int tens;
    int ones;
    int current;
    int snake=sizeof(Snakes)/sizeof(Snakes[0])-1;
    int ladder=sizeof(Ladders)/sizeof(Ladders[0])-1;
    for(tens=90; tens>=0;tens-=10){
        //evens go right to left
        if(tens%20==0){
            for(ones=1;ones<=10;ones++){
                current=tens+ones;
                if(current==position)cout<<"(P)"<<"\t";
                else if(current==Snakes[snake]){
                    cout<<"S"<<"\t";
                    snake--;
                }
                else if(current==Ladders[ladder]){
                    cout<<"L"<<"\t";
                    ladder--;
                }
                else{

                    cout<<current<<"\t";
                }
            }
        }
            //odds go left to right
        else{
            for(ones=10;ones>0;ones--){
                current=tens+ones;
                if(current==position)cout<<"P"<<"\t";
                else if(current==Snakes[snake]){
                    cout<<"S"<<"\t";
                    snake--;
                }
                else if(current==Ladders[ladder]){
                    cout<<"L"<<"\t";
                    ladder--;
                }
                else{

                    cout<<current<<"\t";
                }
            }
        }
        cout<<"\n";
    }//end of for loop for tens dig

}

void Player::move(int roll) {
    int new_pos=roll+position;
    switch (new_pos) {
        case 2:
            position =23;
            cout<<player_name<<" climbed a ladder from 2 to 23!"<<endl;
            break;
        case 8:
            position =34;
            cout<<player_name<<" climbed a ladder from 8 to 34!"<<endl;
            break;
        case 20:
            position =77;
            cout<<player_name<<" climbed a ladder from 20 to 77!"<<endl;
            break;
        case 32:
            position =68;
            cout<<player_name<<" climbed a ladder from 32 to 68!"<<endl;
            break;
        case 41:
            position =79;
            cout<<player_name<<" climbed a ladder from 41 to 79!"<<endl;
            break;
        case 74:
            position =88;
            cout<<player_name<<" climbed a ladder from 74 to 88!"<<endl;
            break;
        case 82:
            position =100;
            cout<<player_name<<" climbed a ladder from 82 to 100!!!"<<endl;
            break;
        case 85:
            position =95;
            cout<<player_name<<" climbed a ladder from 85 to 95!"<<endl;
            break;
        case 97:
            position =25;
            cout<<player_name<<" slid down a snake from 97 to 25."<<endl;
            break;
        case 92:
            position =70;
            cout<<player_name<<" slid down a snake from 92 to 70."<<endl;
            break;
        case 86:
            position =54;
            cout<<player_name<<" slid down a snake from 86 to 54."<<endl;
            break;
        case 62:
            position =37;
            cout<<player_name<<" slid down a snake from 62 to 37."<<endl;
            break;
        case 53:
            position =33;
            cout<<player_name<<" slid down a snake from 53 to 33."<<endl;
            break;
        case 47:
            position =16;
            cout<<player_name<<" slid down a snake from 47 to 16."<<endl;
            break;
        case 38:
            position =15;
            cout<<player_name<<" slid down a snake from 38 to 15."<<endl;
            break;
        case 29:
            position =9;
            cout<<player_name<<" slid down a snake from 29 to 9."<<endl;
            break;

        default:
            cout<<player_name<<" moved from "<<position<<" to "<< new_pos<<"."<<endl;
            position = new_pos;

    }
}


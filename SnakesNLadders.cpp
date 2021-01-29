//@file SnakesNLadders.cpp
//@Author Eleni Polichronakis
//@date October 2020
//@brief this is the main class for the midterm project 

#include "Player.h"
#include "Person.h"
#include "Computer.h"
#include "DE1SoCfpga.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Physical base address of FPGA Devices 
const unsigned int LW_BRIDGE_BASE 	= 0xFF200000;  // Base offset 

// Length of memory-mapped IO window 
const unsigned int LW_BRIDGE_SPAN 	= 0x00DEC700;  // Address map size


//0xFFFEC600 -0xFF200000 = 0xDEC600
const  unsigned  int  MPCORE_PRIV_TIMER_LOAD_OFFSET  =  0xDEC600;             //  Points  to  LOAD Register
const  unsigned  int  MPCORE_PRIV_TIMER_COUNTER_OFFSET  =  0xDEC604;        //  Points  to COUNTER Register
const  unsigned  int  MPCORE_PRIV_TIMER_CONTROL_OFFSET  =  0xDEC608;        //  Points  to CONTROL Register
const  unsigned  int  MPCORE_PRIV_TIMER_INTERRUPT_OFFSET  =  0xDEC60C;    //  Points  to INTERRUPT Register

const unsigned int JP1 =0x00000060;
const unsigned int JP2 =0x00000070;


using namespace std;

void playSnakesNLadders();
void toneGenerator();
float getFreq();

int main() {
    // Main Menu
    int choice=0;
    while(choice!=3){ //while the user does not want to exit
        //Print the Menu and options
        cout<<"Main Menu:"<<endl;
        cout<<"1. Tone Generator"<<endl;
        cout<<"2. Play Snakes and Ladders"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Select an option:"<<endl;
        cin>>choice;

        //Switch case to act based on user's choice
        switch (choice){
            case 1:
                cout<<"You selected tone generator!"<<endl;
                toneGenerator();
                break;
            case 2:
                cout<<"You selected Play Snakes and Ladders"<<endl;
                playSnakesNLadders();
                break;
            case 3:
                cout<<"You selected exit, goodbye!"<<endl;
                break;
            default:
                cout<<"Next time please choose 1,2, or 3"<<endl;
                break;
        }//end of switch case
    }//end of while loop

    return 0;
}
//this function is the actual game/game mechanics
void playSnakesNLadders(){
  //set up random using computer time
    srand(time(NULL));//choose seed value
    int choice=0;
    //create variables to hold names of players
    string player1_name="";
    string player2_name="";
    while(choice!=3){ //while the user does not want to exit
        //Print the Menu and options
        cout<<"Snakes and Ladders Menu:"<<endl;
        cout<<"1. Single Player"<<endl;
        cout<<"2. Two Player"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Select an option:"<<endl;
        cin>>choice;
        if(choice==1){ //Single player game
        
        cout<<"You will play against the computer. "<<endl;
                player2_name="Computer";
                //create the CPU
                Computer player2;
                //Set the CPU's name
                player2.setPlayerName(player2_name);
                cout<<"What is your name?"<<endl;
                cin>>player1_name;
                //Create the Player 1 object
                Person player1;
                //set the player's name
                player1.setPlayerName(player1_name);
                int gameWon=0;// 0 means the game is ongoing
                   while(gameWon==0){//while the game is not over
                       player1.TakeTurn();//player one goes
                       if(player1.getPosition()<100){//if player 1 does not win
                           player2.TakeTurn();//then player 2 goes
                       }
                       else{//if player 1 won
                           gameWon=1;//set the value to 1
                           cout<<"You Won!"<<endl;//congratulate the user
                       }
                       if(player2.getPosition()>=100){// check after player 2 goes if they won
                           gameWon=1;// end the game
                           cout<<"The computer won. :( Nice try!"<<endl;//Sad face for user
                       }
                   }//end of this game
        
        }//end of single player
        else if(choice==2){ //two player game--- largely the same a single player but create two "Person" objects instead of a person and a computer 
        
                cout<<"Two Player: "<<endl;
        
                cout<<"Player 1: What is your name?"<<endl;
                cin>>player1_name;
                //Create Player 1 object and set their name
                Person player1;
                player1.setPlayerName(player1_name);
                cout<<"Player 2: What is your name?"<<endl;
                cin>>player2_name;
                //create player 2 object and set their name
                Person player2;
                player2.setPlayerName(player2_name);
                int gameWon=0;// 0 means the game is ongoing
                   while(gameWon==0){
                       player1.TakeTurn();
                       if(player1.getPosition()<100){
                           player2.TakeTurn();
                       }
                       else{
                           gameWon=1;
                           cout<<player1_name<<": You Won!\n\n\n\n\n"<<endl;
                       }
                       if(player2.getPosition()>=100){
                           gameWon=1;
                           cout<<player2_name<<": You Won!\n\n\n\n\n"<<endl; 
                       }
                   }//end of this game
            }//end of two player
    }//end of while loop for the entire snakes and ladders menu/game

}

//This function is the "tone generator"
void toneGenerator(){
  DE1SoCfpga *speaker = new DE1SoCfpga;
  
  //Configure the direction register to output for the 0 pin
  speaker->RegisterWrite(JP1+4,1);
  //Store initial time conditions
  int load = speaker->RegisterRead(MPCORE_PRIV_TIMER_LOAD_OFFSET);
  int control = speaker->RegisterRead(MPCORE_PRIV_TIMER_CONTROL_OFFSET);
  int interrupt = speaker->RegisterRead(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET);
  
  //set the default length and frequency
  int length=1000;
  float freq=440;
  
  int choice=0;
    while(choice!=4){ //while the user does not want to exit
        //Print the Menu and options
        cout<<"Tone Generator Menu:"<<endl;
        cout<<"1. Enter a specific frequency (ex. 440Hz)"<<endl;
        cout<<"2. Enter a specific note (ex. C4)"<<endl;
        cout<<"3. Change the length of tone"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Select an option:"<<endl;
        cin>>choice;

        //Switch case to act based on user's choice
        switch (choice){
            case 1:
                do{
                cout<<"Enter a specific frequency between 261.6 and 1046.5"<<endl;
                cin>>freq;
                }while(freq<261.6&&freq>1046.5);
                break;
            case 2:
                cout<<"You selected enter a specific note "<<endl;
                freq=getFreq();
                break;
            case 3:
                cout<<"Enter the length of the note "<<endl;
                cin>>length;
                break;
            case 4:
                cout<<"You selected exit, goodbye!"<<endl;
                break;
            default:
                cout<<"Next time please choose 1,2, 3 or 4"<<endl;
                break;
        }//end of switch case
        //Actually play the tone

        int count_low=((200000000.0)/freq)/2.0; //calculate the countdown based on a 200MHz clock
        int run=0;
  //first write an initial count to the load register 
  speaker->RegisterWrite(MPCORE_PRIV_TIMER_LOAD_OFFSET,count_low);
  //the timer can then be started by setting the enable bit E in the control register to 1
  speaker->RegisterWrite(MPCORE_PRIV_TIMER_CONTROL_OFFSET,3); //sets A and E to 1

int current;
while(run<length){
    if(speaker->RegisterRead(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET)!=0){
      speaker->RegisterWrite(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET,1);
        //reset timer flag bit
        run++;
        //get the current value
        current=speaker->RegisterRead(JP1);
        speaker->RegisterWrite(JP1,~current);
    }//end of if statement

  }//end of while loop for playing the tone

    }//end of while loop for tone generator... meaning we are making it back to the main menu
  speaker->RegisterWrite(MPCORE_PRIV_TIMER_LOAD_OFFSET,load);
  speaker->RegisterWrite(MPCORE_PRIV_TIMER_CONTROL_OFFSET,control);
  speaker->RegisterWrite(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET,interrupt);
  
 delete speaker;
 cout<<"Terminating . . .!"<<endl;
}


//This function just allows the user to enter a specific note and get the frequency for the tone generator 
float getFreq(){
  char letter;
  int number;
  cout<<"Enter the letter"<<endl;
  cin>>letter;
  switch(letter){
    case 'C': case 'c':
      cout<<"Choose 4, 5, or 6: "<<endl;
      cin>>number;
      if(number==4) return 261.6;
      else if(number==5) return 523.25;
      else return 1047;
      break;
    case 'D': case'd':
      cout<<"Choose 4 or 5: "<<endl;
      cin>>number;
      if(number==4) return 293.67;
      else return 587.3;
      break;
    case 'E': case'e':
      cout<<"Choose 4 or 5: "<<endl;
      cin>>number;
      if(number==4) return 329.6;
      else return 659.3;
      break;
    case 'F': case'f':
      cout<<"Choose 4 or 5: "<<endl;
      cin>>number;
      if(number==4) return 349.2;
      else return 698.5;
      break;
    case 'G': case'g':
      cout<<"Choose 4 or 5: "<<endl;
      cin>>number;
      if(number==4) return 392.0;
      else return 784.0;
      break;
    case 'A': case'a':
      cout<<"Choose 4 or 5: "<<endl;
      cin>>number;
      if(number==4) return 440;
      else return 880;
      break;
    case 'B': case'b':
      cout<<"Choose 4 or 5: "<<endl;
      cin>>number;
      if(number==4) return 493.9;
      else return 987.8;
      break;
    default:
      break;
  }
  return 440;
  }

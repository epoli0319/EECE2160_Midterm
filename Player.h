//@file Player.h
//@Author Eleni Polichronakis
//@date October 2020
//@brief This is the header file for the player class

#ifndef Player_H
#define Player_H
#include <string>

class Player{
public:
    int position;
    std::string player_name;
    Player();
    void setPlayerName(std::string name);
    void move(int roll);
    int getPosition();
    void printBoard();
    int diceRoll();
};
#endif







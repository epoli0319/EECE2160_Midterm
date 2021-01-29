//@file Computer.h
//@Author Eleni Polichronakis
//@date October 2020
//@brief This is the header file for the computer class which inherits the Player class

#ifndef Computer_H
#define Computer_H
#include "Player.h"//it gets all the methods from the player class too

class Computer : public Player{
public:
    void TakeTurn();
};
#endif

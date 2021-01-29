//@file Person.h
//@Author Eleni Polichronakis
//@date October 2020
//@brief This is the header file for the person class which inherits the Player class

#ifndef Person_H
#define Person_H
#include "Player.h"//it gets all the methods from the player class too

class Person : public Player{
public:
    void TakeTurn();
};
#endif
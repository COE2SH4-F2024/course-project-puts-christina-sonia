#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

#define xBound 18
#define yBound 8

class Player
{
    // Construct the remaining declaration from the project manual.
    // Only some sample members are included here
    // You will include more data members and member functions to complete your design.

    
    public:

        //Direction states:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos() const;      
        void updatePlayerDir();
        void movePlayer(Food& myfood, GameMechs& gm);
        bool checkSelfCollision();


        // More methods to be added here

    private:
              
        objPosArrayList* playerPosList; 
        enum Dir myDir;
        
        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif
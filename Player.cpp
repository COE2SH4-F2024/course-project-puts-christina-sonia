#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef -> getBoardSizeX()/2;
    playerPos.pos->y = mainGameMechsRef -> getBoardSizeY()/2;
    playerPos.symbol ='@';
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    
    return playerPos;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef -> getInput();
        // PPA3 input processing logic  
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case 'w':
            case 'W':
                if (myDir == LEFT || myDir == RIGHT || myDir == STOP){
                    myDir = UP;
                }
                break;
                
            
            case 'a':
            case 'A':
                if (myDir == UP || myDir == DOWN || myDir == STOP){
                myDir = LEFT;
                }
                break;

            case 's':
            case 'S':
                if (myDir == LEFT || myDir == RIGHT ||myDir == STOP){
                myDir = DOWN;
                }
                break;
                

            case 'd':
            case 'D':
                if (myDir == UP || myDir == DOWN || myDir == STOP){
                myDir = RIGHT;
                }
                break;
        }
    }
                

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

// More methods to be added
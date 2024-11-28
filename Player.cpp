#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList();

    objPos headPos(thisGMRef->getBoardSizeX() / 2, thisGMRef->getBoardSizeY() / 2, '@');

    // more actions to be included
    // playerPos.pos->x = mainGameMechsRef -> getBoardSizeX()/2;
    // playerPos.pos->y = mainGameMechsRef -> getBoardSizeY()/2;
    // playerPos.symbol ='*';

    playerPosList->insertHead(headPos);
}


Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    
    return playerPosList;
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
                if (myDir != DOWN){
                    myDir = UP;
                }
                break;
    
            case 'a':
            case 'A':
                if (myDir != RIGHT){
                myDir = LEFT;
                }
                break;

            case 's':
            case 'S':
                if (myDir != UP){
                myDir = DOWN;
                }
                break;
                

            case 'd':
            case 'D':
                if (myDir != LEFT){
                myDir = RIGHT;
                }
                break;
        }
    }                

}

void Player::movePlayer()
{
    
    switch(myDir)
    {
        case LEFT:
            playerPos.pos->x--;
            break;
        case RIGHT:
            playerPos.pos->x++;
            break;
        case UP:
            playerPos.pos->y--;
            break;
        case DOWN:
            playerPos.pos->y++;
            break;
    }

    //iter3: feature 2, insert tmp objpos to head of list, check if new temp objpos overlaps the food pos (get from game mechs class)
//use iposequal() from object class

//if overlapped, foodconsumed do not remove snake and take the respective actions to increase the tail
//if no overlap, remove tail, complete movement


    int playerX = playerPosList.pos->x;
    int playerY = playerPosList.pos->y;

    if (playerX < 1) //wraparound logic
    {
        playerPos.pos->x = (mainGameMechsRef->getBoardSizeX() - 2);
    }
    else if (playerX > 18)
    {
        playerPos.pos->x = 1;
    }
    if (playerY < 1)
    {
        playerPos.pos->y = (mainGameMechsRef->getBoardSizeY() - 2);
    }
    else if (playerY > 8) //dont hard code: fix!
    {
        playerPos.pos->y = 1;
    }   

    
}

// More methods to be added
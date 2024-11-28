#include "Player.h"
#include "MacUILib.h"

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
    // {UP, DOWN, LEFT, RIGHT, STOP}
    switch(myDir)
    {
        case LEFT:
            playerPosList->getHeadElement().pos->x--;
            break;
        case RIGHT:
            playerPosList->getHeadElement().pos->x++;
            break;
        case UP:
            playerPosList->getHeadElement().pos->y--;
            break;
        case DOWN:
            playerPosList->getHeadElement().pos->y++;
            break;
    }

    MacUILib_printf("Current pos is x: %d, y: %d\n\n", playerPosList->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y);
    //iter3: feature 2, insert tmp objpos to head of list, check if new temp objpos overlaps the food pos (get from game mechs class)
//use iposequal() from object class

//if overlapped, foodconsumed do not remove snake and take the respective actions to increase the tail
//if no overlap, remove tail, complete movement


    int playerX = playerPosList->getHeadElement().pos->x;
    int playerY = playerPosList->getHeadElement().pos->y;

    if (playerX < 1) //wraparound logic
    {
        playerPosList->getHeadElement().pos->x = (mainGameMechsRef->getBoardSizeX() - 2);
    }
    else if (playerX > 18)
    {
        playerPosList->getHeadElement().pos->x = 1;
    }
    if (playerY < 1)
    {
        playerPosList->getHeadElement().pos->y = (mainGameMechsRef->getBoardSizeY() - 2);
    }
    else if (playerY > 8) //dont hard code: fix!
    {
        playerPosList->getHeadElement().pos->y = 1;
    }   

    
}



void Player::moveList() //int represents enumeration location
{
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        switch (myDir)
        {
        case UP:
            playerPosList->getElement(i).pos->x--;
            break;
        case DOWN:
            playerPosList->getElement(i).pos->x++;
            break;
        case LEFT:
            playerPosList->getElement(i).pos->y--;
            break;
        case RIGHT:
            playerPosList->getElement(i).pos->y++;
            break;
        }
    }

    playerPosList->removeTail(); //delete tail element
    
    
}

int Player::getFSM()
{
    return myDir;
}
// More methods to be added
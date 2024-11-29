#include "Player.h"
#include "MacUILib.h"
#include "Food.h"

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

void Player::movePlayer(Food myfood)
{
    // {UP, DOWN, LEFT, RIGHT, STOP}
    switch(myDir)
    {
        case LEFT:
            playerPosList->setHeadPosX(playerPosList->getHeadElement().pos->x - 1);
            break;
        case RIGHT:
            playerPosList->setHeadPosX(playerPosList->getHeadElement().pos->x + 1);
            break;
        case UP:
            playerPosList->setHeadPosY(playerPosList->getHeadElement().pos->y - 1);
            break;
        case DOWN:
            playerPosList->setHeadPosY(playerPosList->getHeadElement().pos->y + 1);
            break;
    }

    if (playerPosList->getHeadElement().pos->x == myfood.getFoodPos().pos->x && playerPosList->getHeadElement().pos->y == myfood.getFoodPos().pos->y)
    {
        playerPosList->insertHead(myfood.getFoodPos());
        myfood.generateFood(playerPosList->getHeadElement(), 18, 8); // CHANGE BOARD SIZE
        growth = true;
    }

    else{
        growth = false;
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
        playerPosList->setHeadPosX(mainGameMechsRef->getBoardSizeX() - 2);
    }
    else if (playerX > 18)
    {
        playerPosList->setHeadPosX(1);
    }
    if (playerY < 1)
    {
        playerPosList->setHeadPosY(mainGameMechsRef->getBoardSizeY() - 2);
    }
    else if (playerY > 8) //dont hard code: fix!
    {
        playerPosList->setHeadPosY(1);
    }   

    
}



void Player::moveList() //int represents enumeration location
{
    for (int i =playerPosList->getSize()-1;i>0;i--){
        playerPosList ->setPosX(i, playerPosList->getElement(i-1).pos->x);
        playerPosList ->setPosY(i, playerPosList->getElement(i-1).pos->y);
    }
    // for (int i = 1; i < playerPosList->getSize(); i++)
    // {
    //     switch (myDir)
    //     {
    //     case UP:
    //         playerPosList->setPosX(i, playerPosList->getElement(i).pos->x--);
    //         break;
    //     case DOWN:
    //         playerPosList->setPosX(i, playerPosList->getElement(i).pos->x++);
    //         break;
    //     case LEFT:
    //         playerPosList->setPosY(i, playerPosList->getElement(i).pos->y--);
    //         break;
    //     case RIGHT:
    //         playerPosList->setPosY(i, playerPosList->getElement(i).pos->y++);
    //         break;
    //     }
    // }

    if(!growth){
        playerPosList->removeTail(); //delete tail element
    }
}

int Player::getFSM()
{
    return myDir;
}
// More methods to be added
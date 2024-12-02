#include "Player.h"
#include "MacUILib.h"
#include "GameMechs.h" 
#include "Food.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList();

    objPos headPos(thisGMRef->getBoardSizeX() / 2, thisGMRef->getBoardSizeY() / 2, '@');

    playerPosList->insertHead(headPos);
}


Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
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

bool Player::checkSelfCollision()
{
    // checks every element in the snake body to see if head collides

    for (int i=1; i<playerPosList->getSize(); i++){
        if (playerPosList->getHeadElement().pos->x == playerPosList->getElement(i).pos->x
            && playerPosList->getHeadElement().pos->y == playerPosList ->getElement(i).pos->y)
        {
            return true;
        }
    }

    return false;
}

void Player::movePlayer(Food& myfood, GameMechs& gm)
{

    objPos food;
    objPos nextPos;

    //Initalize the nextPosition to the current head position
    objPos nextPosition(playerPosList ->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y, basicFood);

    //Update nextPosition based on direction state
    switch(myDir)
    {
        case LEFT:
            nextPosition.setObjPos(nextPosition.pos->x-1, nextPosition.pos->y, nextPosition.symbol);
            break;
        case RIGHT:
            nextPosition.setObjPos(nextPosition.pos->x+1, nextPosition.pos->y, nextPosition.symbol);
            break;
        case UP:
            nextPosition.setObjPos(nextPosition.pos->x, nextPosition.pos->y-1, nextPosition.symbol);
            break;
        case DOWN:
            nextPosition.setObjPos(nextPosition.pos->x, nextPosition.pos->y+1, nextPosition.symbol);
            break;
    }


    if (checkSelfCollision() == true){
        gm.setLoseFlag();
        gm.setExitTrue();
    }

    bool foodConsumed = false;

    // if the snake overlaps any of the food, foodconsumed is true
    // then take appropriate actions depending on food type

    for (int i=0; i<myfood.bucketSize(); i++)
    {
        // variables to hold positions
        nextPos = nextPosition.getObjPos();
        food = myfood.getFoodPos(i);

        if (nextPos.isPosEqual(&food)){
            foodConsumed = true;
            if (food.symbol == basicFood)
            {
                playerPosList ->insertHead(nextPosition.getObjPos());
                gm.incrementScore(*playerPosList);
                myfood.generateFood(*playerPosList, xBound, yBound);
            }
        
            else if(food.symbol == specFood1)
            {
                playerPosList ->insertHead(nextPosition.getObjPos());
                gm.incrementScore(*playerPosList); // increment score twice
                gm.incrementScore(*playerPosList);
                myfood.generateFood(*playerPosList, xBound, yBound);
            }
            else if(food.symbol == specFodod2)
            {
                playerPosList ->insertHead(nextPosition.getObjPos());
                gm.incrementScore(*playerPosList); // increment score by three
                gm.incrementScore(*playerPosList); 
                gm.incrementScore(*playerPosList);
                myfood.generateFood(*playerPosList, xBound, yBound);
            }
        }
    }

    //if food is not being consumed, remove tail
    if(!foodConsumed){
        playerPosList ->insertHead(nextPosition.getObjPos());
        playerPosList ->removeTail();
    }


    int playerX = playerPosList->getHeadElement().pos->x;
    int playerY = playerPosList->getHeadElement().pos->y;

    //wraparound logic
    if (playerX < 1)
    {
        playerPosList->setHeadPosX(mainGameMechsRef->getBoardSizeX() - 2);
    }
    else if (playerX > xBound)
    {
        playerPosList->setHeadPosX(1);
    }
    if (playerY < 1)
    {
        playerPosList->setHeadPosY(mainGameMechsRef->getBoardSizeY() - 2);
    }
    else if (playerY > yBound) //dont hard code: fix!
    {
        playerPosList->setHeadPosY(1);
    }   
    

}
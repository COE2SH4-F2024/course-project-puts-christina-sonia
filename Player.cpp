#include "Player.h"
#include "MacUILib.h"
#include "GameMechs.h" // added this 
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

bool Player::checkSelfCollision()
{
    for (int i=1; i<playerPosList->getSize(); i++){
        if (playerPosList->getHeadElement().pos->x == playerPosList->getElement(i).pos->x
            && playerPosList->getHeadElement().pos->y == playerPosList ->getElement(i).pos->y)
        {
            return true;
        }
    }

    return false;
}

void Player::movePlayer(Food& myfood, GameMechs& gm) // added gamemechs count
{


    objPos nextPosition(playerPosList ->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y,'O');
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

    playerPosList ->insertHead(nextPosition.getObjPos());

    if (checkSelfCollision() == true){
        gm.setLoseFlag();
        gm.setExitTrue();
    }

    // if overlapped, food is consumed (do not remove snake and take repspective actions tp increase tail)
    if (playerPosList->getHeadElement().pos->x == myfood.getFoodPos().pos->x && playerPosList->getHeadElement().pos->y == myfood.getFoodPos().pos->y) //nextPosition.isPosEqual(myfood->get) == 1
    {
        myfood.generateFood(*playerPosList, 18, 8); // CHANGE BOARD SIZE
        gm.incrementScore(*playerPosList); // added this 
    }
    else
    {
        playerPosList->removeTail();
    }

    //iter3: feature 2, insert tmp objpos to head of list, check if new temp objpos overlaps the food pos (get from game mechs class)
    //use iposequal() from object class

    //if overlapped, foodconsumed do not remove snake and take the respective actions to increase the tail
    //if no overlap, remove tail, complete movement


    int playerX = playerPosList->getHeadElement().pos->x;
    int playerY = playerPosList->getHeadElement().pos->y;
    bool wrapAround = false;

    if (playerX < 1) //wraparound logic
    {
        playerPosList->setHeadPosX(mainGameMechsRef->getBoardSizeX() - 2);
    }
    else if (playerX > 18)
    {
        playerPosList->setHeadPosX(1);
        wrapAround = true;
    }
    if (playerY < 1)
    {
        playerPosList->setHeadPosY(mainGameMechsRef->getBoardSizeY() - 2);
        wrapAround = true;
    }
    else if (playerY > 8) //dont hard code: fix!
    {
        playerPosList->setHeadPosY(1);
        wrapAround = true;
    }   
    

}
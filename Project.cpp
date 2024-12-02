#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000 



Player *myPlayer; 
GameMechs *myGM;
Food* myFood;

int boardX;
int boardY;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false) 
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    // intializing three food items
    myFood = new Food(3); 

    boardX = myGM->getBoardSizeX();
    boardY = myGM->getBoardSizeY();

}

void GetInput(void)
{
    myGM->collectAsyncInput();
}

void RunLogic(void)
{

    myPlayer ->updatePlayerDir();
    myGM->clearInput();
    myPlayer->movePlayer(*myFood, *myGM); 
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPosArrayList* playerPos = myPlayer->getPlayerPos();

    objPos temp; // holds food positions
    objPos thisSeg; // holds snake body elements

    int playerSize = playerPos->getSize();
    bool used;
    
    //For every element of the board:
    for (int i = 0; i < boardY; i++){
        for (int j = 0; j < boardX; j++){  
            used = false;

            //Print snake if thisSeg is equal to the position
            // on the board
            for (int k = 0; k < playerSize; k++)
            {
                thisSeg = playerPos->getElement(k);
                if (thisSeg.pos->x == j && thisSeg.pos->y == i)
                {
                    MacUILib_printf("%c", thisSeg.symbol);
                    used = true;
                }
            }

            //Otherwise check if the current location matches a food location,
            //if so print the food
            if (used == false)
            {

                for (int s=0; s<myFood->bucketSize(); s++){
                    temp.setObjPos(myFood->getFoodPos(s));
                    if (temp.pos->x == j && temp.pos->y == i){
                         MacUILib_printf("%c", temp.symbol);
                         used = true;
                    }
                }
            }

            // if the current iteration matches the border location print '#'
            // otherwise print a space
            if (used == false)
            {
                 if (j == 0 || j == (boardX - 1) || i == 0 || i == (boardY - 1)){ 
                    MacUILib_printf("%c", '#');
                    }
                else{
                        MacUILib_printf(" ");
                    }
            }

            used = true;
            
        }
        MacUILib_printf("\n");
    }

    //Print food point and updating score
    MacUILib_printf("O = 1 point, S = 2 points, $ = 3 points \n");
    MacUILib_printf("Score: %d \n", myGM->getScore()); 

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 

    if (myGM->getLoseFlagStatus() == true)
    {
        MacUILib_printf("Game Over, self-collison :(");
        
    }
    else if (myGM->getExitFlagStatus() == true){
        MacUILib_printf("Force quit, try again!");
    }

    delete myPlayer;
    delete myGM; 
    delete myFood;  

    MacUILib_uninit();
}


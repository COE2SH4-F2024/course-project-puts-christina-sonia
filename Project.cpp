#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 200000 // originally 100000


Player *myPlayer; 
GameMechs *myGM;
Food* myFood;

int boardX;
int boardY; //ensure this is allowed

//class objPos player; // we added this


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
    myFood = new Food(3);

    boardX = myGM->getBoardSizeX();
    boardY = myGM->getBoardSizeY();

}

void GetInput(void)
{
    myGM->collectAsyncInput();
    //if (myGM->getInput()=='t'){
    //     myFood -> generateFood(myPlayerList[0]->getPlayerPos(), boardX, boardY);
    // } // not sure if this is what they meant but it works

}

void RunLogic(void)
{

    myPlayer ->updatePlayerDir();

    //myGM->getScore(); // used to be incrementScore
    myGM->clearInput();
    //call Food function generation here? (initialize?)
    myPlayer->movePlayer(*myFood, *myGM); // HI SONIA: dereference myFood was the fix. Please verify!
    //myPlayer->moveList();
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPosArrayList* playerPos = myPlayer->getPlayerPos();
    int playerSize = playerPos->getSize();
    bool used, print = false;
    objPos temp;

    for (int i = 0; i < boardY; i++){
        for (int j = 0; j < boardX; j++){  //COLUMNS = 20
            used = false;
            for (int k = 0; k < playerSize; k++)
            {
                objPos thisSeg = playerPos->getElement(k);
                if (thisSeg.pos->x == j && thisSeg.pos->y == i)
                {
                    MacUILib_printf("%c", thisSeg.symbol);
                    used = true;
                }
                //iter 3: check if current segment at y position matches the (j,i) coordinates
                //if yes, print the symbol
                //need to skip if else lock below if have printed something in the for loop
                
            }

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

            if (used == false)
            {
                 if (j == 0 || j == (boardX - 1) || i == 0 || i == (boardY - 1)){ //print the '#' symbol when i = 0 or i = 9 and j = 0 or j = 19 to establish the static frame
                    MacUILib_printf("%c", '#');
                    }
                else{
                        MacUILib_printf(" ");
                    }
            }

            used = true;
               
            
            // else if (playerPos.pos->x == j && myPlayer->getPlayerPos().pos->y == i){
            //     MacUILib_printf("%c", myPlayer->getPlayerPos().symbol); //from myPlayer pointer object, invoke getPlayerPos() member function and retrieve symbol
            // } 
            
        }
        MacUILib_printf("\n");
    }
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

    delete myPlayer;
    delete myGM; 
    delete myFood;  

    MacUILib_uninit();
}


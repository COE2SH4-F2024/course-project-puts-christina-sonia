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
    myFood = new Food();

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

    myGM->incrementScore();
    myGM->clearInput();

    myPlayer->movePlayer(*myFood); // HI SONIA: dereference myFood was the fix. Please verify!
    //myPlayer->moveList();
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPosArrayList* playerPos = myPlayer->getPlayerPos();
    int playerSize = playerPos->getSize();
    bool used;

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
                if (j == 0 || j == (boardX - 1) || i == 0 || i == (boardY - 1)){ //print the '#' symbol when i = 0 or i = 9 and j = 0 or j = 19 to establish the static frame
                MacUILib_printf("%c", '#');
                }
            // else if (playerPos.pos->x == j && myPlayer->getPlayerPos().pos->y == i){
            //     MacUILib_printf("%c", myPlayer->getPlayerPos().symbol); //from myPlayer pointer object, invoke getPlayerPos() member function and retrieve symbol
            // } 
                else if (myFood->getFoodPos().pos->x == j && myFood->getFoodPos().pos->y == i){
                    MacUILib_printf("%c", myFood->getFoodPos().symbol);
                }           
                else{
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Current pos is x: %d, y: %d\n\n", myPlayer->getPlayerPos()->getHeadElement().pos->x, myPlayer->getPlayerPos()->getHeadElement().pos->y);
    MacUILib_printf("Current FSM state: %d", myPlayer->getFSM());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 

    delete myPlayer;
    delete myGM; 
    delete myFood;  

    MacUILib_uninit();
}

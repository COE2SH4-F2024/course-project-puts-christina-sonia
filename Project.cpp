#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000


Player *myPlayer; 
GameMechs *myGM;

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

    /*player.symbol = '@';
    player.pos->x = 10;
    player.pos->y = 5;*/

    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    boardX = myGM->getBoardSizeX();
    boardY = myGM->getBoardSizeY();

}

void GetInput(void)
{
    if (MacUILib_hasChar()){
        char newinput = MacUILib_getChar();
        myGM->setInput(newinput);

    }
}

void RunLogic(void)
{
    if (myGM->getInput() != 0){
        switch(myGM->getInput())
        {
            case ' ':
                myGM->setExitTrue();
                break;
        
        }
        myPlayer ->updatePlayerDir();

    }

    myGM->incrementScore();
    myGM->clearInput();

    myPlayer->movePlayer();
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    for (int i = 0; i < boardY; i++){
        for (int j = 0; j < boardX; j++){  //COLUMNS = 20
            if (j == 0 || j == (boardX - 1) || i == 0 || i == (boardY - 1)){ //print the '#' symbol when i = 0 or i = 9 and j = 0 or j = 19 to establish the static frame
                MacUILib_printf("%c", '#');
            }
            else if (myPlayer->getPlayerPos().pos->x == j && myPlayer->getPlayerPos().pos->y == i){
                MacUILib_printf("%c", myPlayer->getPlayerPos().symbol); //from myPlayer pointer object, invoke getPlayerPos() member function and retrieve symbol
            }            
            else{
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
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

    MacUILib_uninit();
}

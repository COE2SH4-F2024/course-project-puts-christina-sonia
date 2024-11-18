#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; 
GameMechs *myGM;

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
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    /*int i, j;    
    for (i = 0; i < ROWS; i++){
        for (j = 0; j < COLUMNS; j++){ 
            if (j == 0 || j == (COLUMNS - 1) || i == 0 || i == (ROWS - 1)){ //print the '#' symbol when i = 0 or i = 9 and j = 0 or j = 19 to establish the static frame
                cout << "#";
            }
            else if (i % 4 == 0 && j % 4 == 0){
                cout << "f";
            }
            else if (player.pos->x == j && player.pos->y == i){
                cout << player.symbol;
            }            
            else{
                cout << " ";
            }
        }
        cout << "\n";
    }*/
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

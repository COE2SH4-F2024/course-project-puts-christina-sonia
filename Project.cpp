#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000
#define ROWS 10
#define COLUMNS 20


class objPos player;


bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    player.symbol = '@';
    player.pos->x = 10;
    player.pos->y = 5;

    exitFlag = false;
}

void GetInput(void)
{

}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    int i, j;    
    for (i = 0; i < ROWS; i++)
    {

        for (j = 0; j < COLUMNS; j++)
        {
            
            if (j == 0 || j == (COLUMNS - 1) || i == 0 || i == (ROWS - 1)) //print the '#' symbol when i = 0 or i = 9 and j = 0 or j = 19 to establish the static frame
            {
                cout << "#";
            }
            else if (i % 4 == 0 && j % 4 == 0)
            {
                cout << "f";
            }
            else if (player.pos->x == j && player.pos->y == i)
            {
                cout << player.symbol;
            }            
            else
            {
                cout << " ";
            }
        }
        cout << "\n";
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
}

#include "GameMechs.h"
#include "MacUILib.h"


GameMechs::GameMechs()
{
    input = 0 ;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 20;
    boardSizeY = 10;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0 ;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    // at this moment no, because we dont have a heap member
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    
    return loseFlag;

}

void GameMechs :: collectAsyncInput()
{
    if (MacUILib_hasChar()){
        input = MacUILib_getChar();
    }

    if(input == ' ') exitFlag = true;
}

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore(const objPosArrayList& list) // added argument
{
    score = list.getSize() - 1 ;
    // int increment = 1;
    // score += increment;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{

    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

// More methods should be added here
GameMechs::GameMechs(const GameMechs &other){

    input = other.input;
    exitFlag = other.exitFlag;
    loseFlag = other.loseFlag;
    score = other.score;

    boardSizeX = other.boardSizeX;
    boardSizeY = other.boardSizeY;


}

GameMechs& GameMechs :: operator= (const GameMechs &other){

    if (this != &other){
        input = other.input;
        exitFlag = other.exitFlag;
        loseFlag = other.loseFlag;
        score = other.score;

        boardSizeX = other.boardSizeX;
        boardSizeY = other.boardSizeY;

    }

    return *this;
}

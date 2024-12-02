#include <iostream>

using namespace std;
#include "objPos.h"

objPos::objPos() 
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; 
}

objPos::objPos(int xPos, int yPos, char sym) //constructor
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}


//destructor
objPos::~objPos()
{
    delete pos;
}

//copy constructor
objPos::objPos(const objPos &a)
{
    symbol = a.symbol;
    
    pos = new Pos{a.pos->x, a.pos->y};
    
}

//copy assignment operator
objPos& objPos::operator=(const objPos &a)
{
    if (this != &a) //including this decreases the memory required for your data
    {
        this->symbol = a.symbol;
        this->pos = new Pos{a.pos->x, a.pos->y};
        return *this;
    }
}


void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
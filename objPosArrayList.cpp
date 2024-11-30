#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;

    aList = new objPos[arrayCapacity];

    for (int i = 0; i < arrayCapacity; i++)
    {
        aList[i].pos->x = 0;
        aList[i].pos->y = 0;
        aList[i].symbol = 0; //NULL
    }
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

objPosArrayList::objPosArrayList(const objPosArrayList& other)
{
    listSize = other.listSize;
    arrayCapacity = other.arrayCapacity;

    for (int i = 0; i < listSize; i++)
    {
        aList[i] = other.aList[i];
    }

}

objPosArrayList& objPosArrayList::operator=(const objPosArrayList& other)
{
    if (this == &other)
    {
        listSize = other.listSize;
        arrayCapacity = other.arrayCapacity;

        delete[] aList;

        aList = new objPos[arrayCapacity];

        for (int i = 0; i < listSize; i++)
        {
            aList[i] = other.aList[i];
        }
    }
    return *this;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    
    for (int i = listSize - 1; i > 0; i--)
    {
        aList[i] = aList[i-1];
        
    }

    aList[0].symbol = '@';
    aList[0].pos->x = thisPos.pos->x;
    aList[0].pos->y = thisPos.pos->y;
    
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[listSize++] = thisPos;
}

void objPosArrayList::removeHead()
{
    if (listSize == 0)
        return;

    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i+1];
    }

    listSize--;
}

void objPosArrayList::removeTail()
{
    if (listSize > 0)
    {
        listSize--;
    }
}

objPos objPosArrayList::getHeadElement() const
{
    if (listSize > 0)
    {
        return aList[0];
    }
    return objPos();
}

objPos objPosArrayList::getTailElement() const
{
    if (listSize > 0)
    {
        return aList[listSize-1];
    }
    return objPos();
    
    
}

objPos objPosArrayList::getElement(int index) const
{
    if (index >= 0 && index < listSize)
    {
        return aList[index];
    }
    return objPos(); //if index is out of bounds just return empty object
}

void objPosArrayList::setHeadPosX(int newPosX)
{
    aList[0].pos->x = newPosX;
}

void objPosArrayList::setHeadPosY(int newPosY)
{
    aList[0].pos->y = newPosY;
}

void objPosArrayList::setPosX(int index, int newPosX)
{
    //aList[index].pos->x = newPosX;
    this->aList[index].pos->x = newPosX;
}

void objPosArrayList::setPosY(int index, int newPosY)
{
    //aList[index].pos->y = newPosY;
    this->aList[index].pos->y = newPosY;
}
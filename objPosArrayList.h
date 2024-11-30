#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int listSize;
        int arrayCapacity;

    public:
        objPosArrayList();
        ~objPosArrayList();
        objPosArrayList(const objPosArrayList& other);
        objPosArrayList& operator=(const objPosArrayList& other);


        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();

        void setHeadPosX(int newPosX);
        void setHeadPosY(int newPosY);
        void setPosX(int index, int newPosX);
        void setPosY(int index, int newPosY);

        
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;
};

#endif
#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

using namespace std;

class Food
{
    private:
        //objPos foodPos;
        objPosArrayList* foodBucket;
    
    public:
        Food(); // default constructors
        ~Food(); // destructor

        Food(const Food &other); //copy constructor
        Food& operator= (const Food &other); // copy assignment operator


        void generateFood(objPosArrayList& list, int x_size, int y_size);
        objPos getFoodPos(int index) const;
        int bucketSize() const;
        Food(int size);


};

#endif
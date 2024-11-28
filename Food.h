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
        objPos foodPos;
    
    public:
        Food(); // default constructors
        ~Food(); // destructor

        Food(const Food &other); //copy constructor
        Food& operator= (const Food &other); // copy assignment operator


        void generateFood(objPos blockOff, int x_size, int y_size);
        objPos getFoodPos() const;


};


#endif
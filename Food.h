#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

#define basicFood 'O'
#define specFood1 'S'
#define specFodod2 '$'



using namespace std;

class Food
{
    private:
    
        //objPos foodPos; 
        objPosArrayList* foodBucket; // BONUS - uses list instead of objpos (see above)
    
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
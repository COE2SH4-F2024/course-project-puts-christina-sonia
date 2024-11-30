#include "Food.h"
#include "MacUILib.h"


Food :: Food()
{
 foodPos.pos->x = 3;
 foodPos.pos->y = 4;
 foodPos.symbol = 'O';

}

Food :: ~Food()
{
    // nothing right now
}

Food :: Food(const Food &other){
    this ->foodPos = other.foodPos;
} 

Food& Food :: operator=(const Food &other){
    if (this != &other){
        this ->foodPos = other.foodPos;
    }

    return *this;
}

void Food :: generateFood(objPosArrayList& list, int x_size, int y_size)
{
    srand(time(NULL));
    
    while (true){
        bool overlap = false;
        foodPos.pos->x = rand() % x_size +1;
        foodPos.pos->y = rand() % y_size +1;
    
        for (int i=0; i<list.getSize(); i++){
            objPos playerNow = list.getElement(i);
            if(playerNow.pos->x == foodPos.pos->x && playerNow.pos->y == foodPos.pos->y){
                overlap = true;
                break;
            }
        }

        if (!overlap) // if overlap is false
        {
            break;
        }
    }

    foodPos.symbol = 'O';
}

objPos Food :: getFoodPos() const 
{
    return foodPos;
}

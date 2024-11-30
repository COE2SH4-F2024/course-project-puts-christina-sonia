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

void Food :: generateFood(objPos blockOff, int x_size, int y_size)
{
    srand(time(NULL));
    
    while (true){
        false;
        foodPos.pos->x = rand() % x_size +1;
        foodPos.pos->y = rand() % y_size +1;
    
        if(blockOff.pos->x == foodPos.pos->x && blockOff.pos->y == foodPos.pos->y){
            true;
            break;
        }
    }

    foodPos.symbol = 'O';
}

objPos Food :: getFoodPos() const 
{
    return foodPos;
}
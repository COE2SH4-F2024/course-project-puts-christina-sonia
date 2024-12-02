#include "Food.h"
#include "MacUILib.h"


Food :: Food()
{

    foodBucket = new objPosArrayList();
    foodBucket ->insertTail(objPos(3,4,'O')); // default position and symbol
//  foodPos.pos->x = 3;
//  foodPos.pos->y = 4;
//  foodPos.symbol = 'O';

}

Food :: ~Food()
{
    delete foodBucket;
    // nothing right now
}


Food :: Food(const Food &other){
    foodBucket = new objPosArrayList(*other.foodBucket);
    //this ->foodBucket = other.foodBucket;

} 

Food& Food :: operator=(const Food &other){
    if (this != &other){
        foodBucket = new objPosArrayList(*other.foodBucket);
    }

    return *this;
}

Food :: Food(int size)
{
    int i;
    if (size<3){size = 3;}

    // initializing food with default positions
    foodBucket = new objPosArrayList();
    foodBucket->insertTail(objPos(5,4,'S')); // first sepcial food
    foodBucket->insertTail(objPos(6,3,'$')); // second special food

    // if the size is greater than three, the remaining will be default food
    for (int j=2; j<size; j++){
        foodBucket->insertTail(objPos(3,4,'O'));
    }


}
void Food :: generateFood(objPosArrayList& list, int x_size, int y_size)
{
    srand(time(NULL));

     objPos playerNow;
     objPos canFood;
     int canX, canY;

    for(int i=0; i<foodBucket->getSize(); i++)
    {
        while (true){
            bool overlap = false;
            canX = rand() % x_size +1;
            canY = rand() % y_size +1;

            foodBucket->setElement(objPos(canX, canY,foodBucket->getElement(i).symbol),i);
            canFood = foodBucket->getElement(i);

            //canFood = foodBucket->getElement(i);

            for (int j=0; j<list.getSize(); j++){

                playerNow = list.getElement(j);
                if(canFood.isPosEqual(&playerNow)){
                    overlap = true;
                    break;
                }
            }

            if (!overlap)
            {
                break;
            }

            // if (!overlap) // if overlap is false
            // {
            //     for (int k=0; k<i; k++){
            //         objPos existingFood = foodBucket->getElement(i);
            //         // playerNow = foodBucket ->getElement(k);
            //         if (canFood.isPosEqual(&existingFood)){
            //             overlap = true;
            //             break;
            //         }

            //     }
            // }
           
        }
        // foodBucket->getElement(i).pos->x=canFood.pos->x;
        // foodBucket->getElement(i).pos->x=canFood.pos->x;
    }
    

    //foodPos.symbol = 'O';
}

objPos Food :: getFoodPos(int index) const 
{
    return foodBucket ->getElement(index);
}

int Food:: bucketSize() const // number of food in bucket - added this entire thing
{
    return foodBucket->getSize();
}
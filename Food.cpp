#include "Food.h"
#include "MacUILib.h"


Food :: Food()
{
    foodBucket = new objPosArrayList();
    foodBucket ->insertTail(objPos(3,4, basicFood)); // default position and symbol

}

Food :: ~Food()
{
    delete foodBucket;
}


Food :: Food(const Food &other){

    foodBucket = new objPosArrayList(*other.foodBucket); // deep copy

} 

Food& Food :: operator=(const Food &other){
    
    if (this != &other){
        delete foodBucket;
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
    foodBucket->insertTail(objPos(5,4,specFood1)); // first sepcial food
    foodBucket->insertTail(objPos(6,3,specFodod2)); // second special food

    // if the number of food items is set greater than three,
    // the remaining will be default food

    for (int j=2; j<size; j++){
        foodBucket->insertTail(objPos(3,4,basicFood));
    }


}
void Food :: generateFood(objPosArrayList& list, int x_size, int y_size)
{
    srand(time(NULL));

     objPos playerNow; 
     objPos canFood; //candidate food
     int canX, canY; //candidate x & y coordinates for food location

    for(int i=0; i<foodBucket->getSize(); i++)
    {
        while (true){
            bool overlap = false;
            canX = rand() % x_size +1;
            canY = rand() % y_size +1;

            foodBucket->setElement(objPos(canX, canY,foodBucket->getElement(i).symbol),i);
            canFood = foodBucket->getElement(i);


            //check if food overlaps the snake body list
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
            
        }
    }
    
}

objPos Food :: getFoodPos(int index) const 
{
    return foodBucket ->getElement(index);
}

int Food:: bucketSize() const // number of food in bucket 
{
    return foodBucket->getSize();
}
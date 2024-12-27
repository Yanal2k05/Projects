#include "headerA3.h"

int countCars(a3Car *headLL)  
{
    int count = 0; // count of cars in the linked list

    a3Car *current = headLL; //  Point to the first node in the linked list

    while (current != NULL)
    {

        count++;
        current = current->nextCar; //  Move on to next car
    }

    return count;
}

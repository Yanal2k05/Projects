#include "headerA3.h"


void oneLessCar(a3Car **headLL, int whichOne)
{
    if (*headLL == NULL)
        return; // List is empty

    a3Car *temp = *headLL, *temp2 = NULL; // Intialize temp and temp2 to head of list

    // If the car to be removed is the head of the list
    if (whichOne == 1)
    {
        *headLL = temp->nextCar; // Change head
        free(temp);              // Free old head
        return;
    }

    // Find the car that precedes the one to be removed
    for (int i = 1; temp != NULL && i < whichOne; i++)
    {
        temp2 = temp;
        temp = temp->nextCar;
    }

    // If whichOne is greater than the number of cars
    if (temp == NULL || temp->nextCar == NULL)
        return;

    // Unlink the node from linked list
    temp2->nextCar = temp->nextCar;

    free(temp); // Free memory
}

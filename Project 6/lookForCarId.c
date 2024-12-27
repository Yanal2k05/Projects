#include "headerA3.h"


int lookForCarId(struct car *headLL, int key)
{
    struct car *current = headLL; // Start at the head of the linked list
    int position = 1;             // Initialize position 

    while (current != NULL)
    {
        if (current->carId == key)
        {
            return position; // Found the carId
        }
        current = current->nextCar; // Move to the next car
        position++;                 // Increment position
    }

    return -1; // CarId not found in the list
}

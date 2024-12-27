#include "../include/headerA3.h"

#include <stdbool.h>

// Function to sort the linked list by carId
void sortCarId(struct car **headLL)
{
    bool sort;
    struct car *current; // Inittialize current node as head of linked list
    struct car *next;    // Initialize a new node for next node in LL
    struct car *temp;    // Initialize a temporary node of type car
    struct car **ptr;    // Initialize a pointer which will be used to traverse through the linked list

    if (headLL == NULL || (*headLL)->nextCar == NULL)
    {
        return; 
    }

    do
    {
        sort = false; // Initialize sort to false at the beginning of each pass

        ptr = headLL; // Start the pointer at the head of the linked list

        // Continue looping as long as we're not at the end of the list
        while ((*ptr) != NULL && (*ptr)->nextCar != NULL)
        {
            current = *ptr;         
            next = (*ptr)->nextCar; // The next car in the list

            // If the current car's ID is greater than the next car's ID, we need to swap them
            if (current->carId > next->carId)
            {
                // Swapping the nodes
                temp = next->nextCar;    
                next->nextCar = current; 
                current->nextCar = temp; 
                *ptr = next;             

                sort = true; // Set the sort to true since a swap was made
            }
            ptr = &(*ptr)->nextCar; // Move the pointer forward in the list
        }
    } while (sort); 
}

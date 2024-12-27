#include "headerA3.h"

void noMoreCars(a3Car **headLL)
{

    char option;

    // Loop until valid input ('y' or 'n') is received
    do
    {
        printf("Are you sure you want to remove all car data (enter y for yes, n for no): ");
        scanf(" %c", &option);

        while (getchar() != '\n');

    } while (option != 'y' && option != 'n');

    if (option == 'y')
    {

        a3Car *current = *headLL;
        a3Car *next;

        while (current != NULL)
        {
            next = current->nextCar;
            free(current);  // Free the current node
            current = next; // Move to the next node
        }

        *headLL = NULL; // Set the headLL to NULL to mark it as empty

        printf("All cars have been removed from the list.\n");
    }
        else if (option == 'n')
            {
                printf("No cars removed\n");
            }
    }


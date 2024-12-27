#include "../include/headerA3.h"

#include <stdbool.h>

void printAll(struct car *headLL)
{
    struct car *current = headLL;
    int carPosition = 0; // Initialize the car number

    // Traverse the linked list
    while (current != NULL)
    {
        char formattedPrice[64];                         
        sprintf(formattedPrice, "%.2f", current->price); // Convert to string with 2 decimal places
        int len = strlen(formattedPrice);
        int dotPosition = strchr(formattedPrice, '.') - formattedPrice;
        int insertPositions = (dotPosition - 1) / 3; // Number of commas to insert

        if (insertPositions > 0)
        {
            char temp[64] = {0};                   // Temporary buffer for formatted price with commas
            int tempIndex = len + insertPositions; // Adjust length for commas
            temp[tempIndex] = '\0';                // Null-terminate
            int originalIndex = len - 1;

            for (int i = 0; i < len - dotPosition; ++i)
            { // Copy decimals and dot without changes
                temp[--tempIndex] = formattedPrice[originalIndex--];
            }

            int commasInserted = 0;
            while (originalIndex >= 0)
            { // Copy rest of the string with commas
                temp[--tempIndex] = formattedPrice[originalIndex--];
                if ((++commasInserted % 3) == 0 && originalIndex >= 0)
                {
                    temp[--tempIndex] = ','; // Insert comma every 3 digits
                }
            }

            // Print car details
            printf("Car #: %d\n", ++carPosition);
            printf("Car id: %d\n", current->carId);
            printf("Model: %s\n", current->model);
            printf("Type: %s\n", current->type);
            printf("Price: CDN $%s\n", temp);
        }
        else
        {
            // Print car details without needing to format price
            printf("Car #: %d\n", ++carPosition);
            printf("Car id: %d\n", current->carId);
            printf("Model: %s\n", current->model);
            printf("Type: %s\n", current->type);
            printf("Price: CDN $%s\n", formattedPrice);
        }

        printf("Year of Manufacture: %d\n\n", current->year);

        current = current->nextCar; // Move to the next car
    }

    if (carPosition == 0)
    {
        printf("No cars found.\n");
    }
    else
    {
        printf("Currently, there are %d cars.\n", carPosition); // Print the exact number of cars
    }
}

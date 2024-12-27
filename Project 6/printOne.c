#include "headerA3.h"


void printOne(struct car *headLL, int whichOne)
{
    int count = countCars(headLL); // Count the total number of cars in the linked list

    if (whichOne < 1 || whichOne > count) {
        printf("Invalid position. Please enter a valid position.\n");
        return;
    }

    struct car *current = headLL;

    // Traverse the linked list
    for (int i = 1; i < whichOne; i++) {
        current = current->nextCar;
    }

    // Format price with commas
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
        printf("Car id: %d\n", current->carId);
        printf("Model: %s\n", current->model);
        printf("Type: %s\n", current->type);
        printf("Price: CDN $%s\n", temp);
    }
    else
    {
        // Print car details without needing to format price
        printf("Car id: %d\n", current->carId);
        printf("Model: %s\n", current->model);
        printf("Type: %s\n", current->type);
        printf("Price: CDN $%s\n", formattedPrice);
    }

    printf("Year of Manufacture: %d\n", current->year);
}

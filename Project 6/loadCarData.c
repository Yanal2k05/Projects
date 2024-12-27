#include "headerA3.h"


// Function to load car data from a text file
void loadCarData(struct car **headLL, char fileName[MAX_LENGTH])
{
    FILE *file = fopen(fileName, "r");    // Open the file in read mode
    if (file == NULL)
    {
        printf("Failed to open file %s.\n", fileName); // Error message  when the file is not found
        return;
    }

    char buffer[128]; // Buffer for reading file lines
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        int carId, year;
        double price;
        char model[MAX_LENGTH], type[MAX_LENGTH];  

        // Parse the line
        if (sscanf(buffer, "%d,%[^,],%[^,],%d,%lf", &carId, model, type, &year, &price) == 5)
        {
            // Allocate memory for new car
            struct car *newCar = (struct car *)malloc(sizeof(struct car));
            if (newCar == NULL)
            {
                printf("Memory allocation failed for new car.\n");
                continue;
            }

            // Set the fields for the new car
            newCar->carId = carId;
            strncpy(newCar->model, model, MAX_LENGTH - 1);
            newCar->model[MAX_LENGTH - 1] = '\0'; // Ensure null termination
            strncpy(newCar->type, type, MAX_LENGTH - 1);
            newCar->type[MAX_LENGTH - 1] = '\0'; // Ensure null termination
            newCar->year = year;
            newCar->price = price;
            newCar->nextCar = NULL;

            // Add the new car to the list
            if (*headLL == NULL)
            {
                *headLL = newCar; // List is empty, add first car
            }
            else
            {
                struct car *current = *headLL;
                while (current->nextCar != NULL)
                { // Traverse to the end of the list
                    current = current->nextCar;
                }
                current->nextCar = newCar; // Add the new car at the end
            }
        }
        else
        {
            printf("Failed to parse line: %s\n", buffer);
        }
    }

    fclose(file);
}

#include "../include/headerA3.h"

#include <time.h>

void addNewCar(struct car **headLL)
{
    // Allocate memory for a new car node
    struct car *newCar = (struct car *)malloc(sizeof(struct car));
    if (newCar == NULL)
    {
        printf("Error allocating memory.\n");
        return;
    }

    // Prompt user for car data
    printf("Enter the car model: ");
    fgets(newCar->model, sizeof(newCar->model), stdin);
    newCar->model[strcspn(newCar->model, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the car type: ");
    fgets(newCar->type, sizeof(newCar->type), stdin);
    newCar->type[strcspn(newCar->type, "\n")] = '\0'; // Remove trailing newline

    printf("Enter its year of manufacture: ");
    scanf("%d", &newCar->year);
    getchar(); // Consume newline character after int input

    printf("Enter its price: ");
    scanf("%lf", &newCar->price);
    getchar(); // Consume newline character after int input

    int sum = 0;
    for (int i = 0; newCar->model[i] != '\0'; i++)
    {
        sum += (int)newCar->model[i];
    }
    newCar->carId = sum + strlen(newCar->type);
    int originalId = newCar->carId;

    // Check for uniqueness and handle collisions
    struct car *current = *headLL;
    while (current != NULL)
    {
        if (current->carId == newCar->carId)
        {
            srand(time(NULL)); // Seed random number generator
            do
            {
                newCar->carId = originalId + rand() % 999; // Add random number 
            } while (current->carId == newCar->carId);
            break;
        }
        current = current->nextCar;
    }

    // Insert the new car at the end of the linked list
    if (*headLL == NULL)
    {
        *headLL = newCar;
    }
    else
    {
        current = *headLL;
        while (current->nextCar != NULL)
        {
            current = current->nextCar;
        }
        current->nextCar = newCar;
    }
    newCar->nextCar = NULL;

    printf("Your computer-generated carId is %d\n", newCar->carId);
}
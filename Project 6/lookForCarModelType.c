#include "../include/headerA3.h"

int lookForCarModelType(struct car *headLL, char key[100])
{
    struct car *current = headLL;
    int station = 1; // Start position at 1

    while (current != NULL)
    {

        // add model and type with a space in between
        char modeType[MAX_LENGTH * 2]; // Make sure this is large enough
        sprintf(modeType, "%s %s", current->model, current->type); // Stores string in buffer

        // Convert to lowercase
        for (int i = 0; modeType[i] != '\0'; i++)
        {
            modeType[i] = tolower(modeType[i]);
        }
        for (int i = 0; key[i] != '\0'; i++)
        {
            key[i] = tolower(key[i]);
        }

        // Compare modeType string with the search key
        if (strcspn(modeType, key) == 0)
        {
            return station;
        }

        current = current->nextCar;
        station++;
    }

    return -1; // Not found
}
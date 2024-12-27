#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"


void freeTree(Node *root);


// The main function drives the menu selection loop.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please use following input form: %s 'expression'\n", argv[0]);
        return 1;
    }

    char expr[100];
    int j = 0;

    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (argv[1][i] != '\\') { 
            expr[j++] = argv[1][i];
        }
    }
    expr[j] = '\0';

    Node *root = parseExpression(expr);
    
int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Preorder\n");
        printf("2. Inorder\n");
        printf("3. Postorder\n");
        printf("4. Calculate\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
    
    if (scanf("%d", &choice) != 1) { // Check if input is not a number
        printf("Invalid input. Please enter a number between 1 and 5.\n");

        // Clear the input buffer
        while (getchar() != '\n'); 

        continue; // Prompt user again
    }

        switch (choice) {
            case 1: preorder(root); printf("\n"); break;
            case 2: inorder(root); printf("\n"); break;
            case 3: postorder(root); printf("\n"); break;
            case 4: 
                varCount = 0; // Resetting for each loop
                promptVariables(root);
                printf("Result: %.2f\n", calculate(root));
                break;
            case 5: break;
            default: 
                printf("Please enter a valid choice.\n");
         }
    } while (choice != 5);


  freeTree(root);

  
    return 0;
}




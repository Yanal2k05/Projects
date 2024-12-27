/*
Name: Yanal Abu Rahmeh
Student ID: 1284819
Assignment 2, Question 2
*/

#include "q2.h"
#include <stdio.h>
#include <stdlib.h>


// Push a value to the stack
void push(Operand **stack, double value) {
    Operand *new_operand = (Operand *) malloc(sizeof(Operand)); // Allocate memory for the new operand
    if (!new_operand) {
        printf("Memory allocation error\n"); // Memory allocation error
        exit(1);
    }
    new_operand->value = value; // Set the value of the new operand
    new_operand->next = *stack; // Add the new operand to the stack
    *stack = new_operand;
}

// Pop the top value from the stack
double pop(Operand **stack) {
    if (*stack == NULL) {
        printf("Error: Stack underflow\n"); // Stack underflow
        return 0;
    }
    Operand *temp = *stack; // Temporary pointer to the top of the stack
    double value = temp->value;
    *stack = (*stack)->next; // Move the stack pointer to the next value
    free(temp); // Free the memory of the popped operand
    return value; 
}

// Print the stack
void print(Operand *stack) {
    while (stack != NULL) {
        printf("%.2f -> ", stack->value); // Print the value of the operand
        stack = stack->next;
    }
    printf("NULL\n");
}
// Free the stack
void freeStack(Operand **stack) {
    while (*stack != NULL) {
        Operand *temp = *stack;
        *stack = (*stack)->next;
        free(temp);
    }
}

#include "q2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv){

  // Pointer to the stack
  Operand *stack = NULL;


  if (argc != 2) {
    printf("Usage: %s <postfix-expression>\n", argv[0]); // Print usage
    return 1;
  }

  
  for (int i = 0; i < strlen(argv[1]); ++i) { // Loop through the expression

    char current = argv[1][i]; // Current character

  
    if (isdigit(current)) {
      double value = current - '0';  // Convert char digit to double
      push(&stack, value);
    } else {
      
      double operand2 = pop(&stack);  // Second operand
      double operand1 = pop(&stack);  // First operand

      switch (current) { // Perform the operation
        case '+': 
          push(&stack, operand1 + operand2); // Adding the operands
          break;
        case '-': 
          push(&stack, operand1 - operand2); // Subtracting the operands
          break;
        case '*':
          push(&stack, operand1 * operand2); // Multiplying the operands
          break;
        case '/':
          if (operand2 == 0) { 
            printf("Error: Division by zero\n"); 
            return 1;
          }
          push(&stack, operand1 / operand2); // Diving the operands
          break;
        default:
          printf("Error: Invalid character '%c'\n", current); // Invalid character
          return 1;
      }
    }
  }

  // result in the last value of the stack
  double result = pop(&stack);

  // Print the result 
  printf("Result: %.2f\n", result);

  freeStack(&stack); // Free the stack

  return 0;
}

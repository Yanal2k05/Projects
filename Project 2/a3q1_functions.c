/*
Name: Yanal Abu Rahmeh
Student ID: 1284819
Assignment 3, Question 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"

// Structure to store variables
Variable variables[10];
int varCount = 0;

// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node* createNode(char *data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }
    strcpy(node->data, data);
    node->left = node->right = NULL;
    return node;
}

// Helper function to find the main operator in the expression
int findMainOperator(char *expr) {
    int count = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') count++;
        else if (expr[i] == ')') count--;
        else if ((expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') && count == 0) {
            return i;
        }
    }
    return -1; // No operator found
}


// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
Node* parseExpression(char *expr) {
    // Remove outer parentheses if present
    if (expr[0] == '(' && expr[strlen(expr) - 1] == ')') {
        expr[strlen(expr) - 1] = '\0';
        expr++;
    }

    int operatorPos = findMainOperator(expr);
    if (operatorPos == -1) {
        // If no operator, create a node with the current data
        return createNode(expr);
    }

    // Split the expression into operator, left operand, and right operand
    char operatorChar[2] = {expr[operatorPos], '\0'};
    Node *node = createNode(operatorChar);

    char leftOperand[100], rightOperand[100];
    strncpy(leftOperand, expr, operatorPos);
    leftOperand[operatorPos] = '\0';
    strcpy(rightOperand, &expr[operatorPos + 1]);

    // Recursively parse the left and right subtrees
    node->left = parseExpression(leftOperand);
    node->right = parseExpression(rightOperand);

    return node;
}


// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root) {
    if (root == NULL)
        return;

    printf("%s ", root->data); // Print root data
    preorder(root->left); // Traverse left subtree
    preorder(root->right); // Traverse right subtree
}


// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
void inorder(Node *root) {
    if (root == NULL) 
        return; // Return if the node is NULL

    printf("("); // Print opening parenthesis before traversing left subtree
    inorder(root->left); // Traverse left subtree
    printf("%s", root->data); // Print root data
    inorder(root->right); // Traverse right subtree
    printf(")"); // Print closing parenthesis after traversing right subtree
}


// The postOrder function prints tree nodes in postorder traversal.
void postorder(Node *root) {
    if (root == NULL)
        return;

    postorder(root->left); // Traverse left subtree
    postorder(root->right); // Traverse right subtree
    printf("%s ", root->data); // Print root data
}


// The promptVariables function prompts the user to assign values to each variable found in the expression tree. The values should be stored in the Variables struct.
void promptVariables(Node *root) {
    if (root == NULL)
        return;

    // Check if the current node contains a variable
    if (isalpha(root->data[0])) {
        for (int i = 0; i < varCount; i++) {
            if (strcmp(variables[i].varName, root->data) == 0) {
                return; // Variable already assigned
            }
        }
        // Prompt user to input the variable's value
        printf("Enter value for %s: ", root->data);
        float value;
        if (scanf("%f", &value) != 1) {
            printf("Invalid input. Using default value 0.\n");
            value = 0.0;
        }
        strcpy(variables[varCount].varName, root->data);
        variables[varCount].value = value;
        varCount++;
    }

    // Recursively prompt for variables in left and right subtrees
    promptVariables(root->left);
    promptVariables(root->right);
}


// The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root) {
    if (!root) return 0.0;

    // If the node is a digit or decimal number, return its value
    if (isdigit(root->data[0]) || root->data[0] == '.') {
        return atof(root->data);
    } else if (isalpha(root->data[0])) {
        // If the node is a variable, retrieve its value
        for (int i = 0; i < varCount; i++) {
            if (strcmp(variables[i].varName, root->data) == 0) {
                return variables[i].value;
            }
        }
        // Undefined variable, default to 0
        printf("Error: Variable %s is undefined. Defaulting to 0.\n", root->data);
        return 0.0;
    }

    // Calculate values of left and right subtrees
    float leftValue = calculate(root->left);
    float rightValue = calculate(root->right);

    // Perform the operation based on the operator
    if (strcmp(root->data, "+") == 0) return leftValue + rightValue; // Addition
    if (strcmp(root->data, "-") == 0) return leftValue - rightValue; // Subtraction
    if (strcmp(root->data, "*") == 0) return leftValue * rightValue; // Multiplication   
    if (strcmp(root->data, "/") == 0) // Division 
    
    {
        if (rightValue == 0.0) { // Check for division by zero
            printf("Error: Division by zero!\n"); 
            return 0.0;
        }
        return leftValue / rightValue; // Perform division
    }

    // Unknown operator
    printf("Error: Unknown operator %s!\n", root->data);


    return 0.0;
}


void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);  // Free the left subtree
    freeTree(root->right); // Free the right subtree
    free(root);            // Free the current node
}


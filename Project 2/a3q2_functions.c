/*
Name: Yanal Abu Rahmeh
Student ID: 1284819
Assignment 3, Question 2
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "a3q2_header.h"

/*
 * The downHeap function performs the downheap algorithm.
 * The key at the passed position is swapped with the key of it's child with the largest value.
 * If the key is smaller, than both of it's children's keys then no swap happens.
 * After swap, the downHeap is called again to the new position of the swapped key and it terminates when it's value is smaller than both children.
*/

void downHeap(int key[20], int pos, int array[20][10]) {
    // Calculate the indices of the left and right children of the current node
    int leftChild = 2 * pos + 1;
    int rightChild = 2 * pos + 2;
    int largest = pos; // Assume the current node is the largest

    // Check if the left child exists and is larger than the current largest
    if (leftChild < 20 && key[leftChild] > key[largest]) {
        largest = leftChild;
    }
    // Check if the right child exists and is larger than the current largest
    if (rightChild < 20 && key[rightChild] > key[largest]) {
        largest = rightChild;
    }

    // If the largest is not the current node, swap and recurse
    if (largest != pos) {
        swap(pos, largest, key, array);
        downHeap(key, largest, array); // Recursively downHeap for the affected subtree
    }
}

bool isParent(int keyPos) {
    // A node is a parent if it has at least one child
    return (2 * keyPos + 1) < 20;
}

void swap(int key1Pos, int key2Pos, int key[20], int array[20][10]) {
    // Swap the values in the key array
    int tempKey = key[key1Pos];
    key[key1Pos] = key[key2Pos]; // Swap the values in the key array
    key[key2Pos] = tempKey;

    // Swap the corresponding rows in the 2D array
    int tempRow[10];
    for (int i = 0; i < 10; ++i) {
        tempRow[i] = array[key1Pos][i];
        array[key1Pos][i] = array[key2Pos][i]; // Swap the values in the row
        array[key2Pos][i] = tempRow[i];
    }
}



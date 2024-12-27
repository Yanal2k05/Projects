/*
Name: Yanal Abu Rahmeh
Student ID: 1284819
Assignment 4
Due date: December 1, 2024
course ID: CIS*2520

I have exclusive control over this submission via my password.
By including this statement in this header, I certify that
I have read and understood the University policy in academic
integrity and I assert that this work is my own. Furthermore, I certify that is assignment was prepared 
by me specifically for this course.

*/

#include "graph.h"

/* function will display the primary user interface
    This is already done for you*/
void prompt(void)
{

    printf("\nMenu:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Find Shortest Path using Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}

/**
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */
Graph *readGraph(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename); // Error message
        return NULL; // Return NULL if file could not be opened
    }

    // Allocate memory for the graph structure
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL) {
        printf("Error: Memory allocation failed.\n"); 
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjList[i] = NULL; // Initialize the adjacency list
    }

    int row = 0;
    char line[1024];

    // Read the adjacency matrix from the file
    while (fgets(line, sizeof(line), file)) {
        int col = 0;
        char *token = strtok(line, " ");
        while (token) {
            graph->adjMatrix[row][col] = atoi(token);
            col++;
            token = strtok(NULL, " ");
        }
        row++;
    }

    graph->numVertices = row; // Set the number of vertices

    // Display the adjacency matrix
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }

    fclose(file);
    return graph;
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Error: Memory allocation failed for new node.\n"); // Error message
        return NULL;
    }

    // Initialize the node
    newNode->vertex = vertex;
    newNode->next = NULL;

    return newNode;
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph)
{
    if (graph == NULL) {
        printf("Error with the graph.\n"); // Error message
        return;
    }

    // Display the adjacency list
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Vertex %d:", i + 1);
        Node *current = graph->adjList[i];

        while (current) {
            printf(" -> %d (%d)", current->vertex + 1, graph->adjMatrix[i][current->vertex]); // Display 1-based index
            current = current->next;
        }
        printf(" NULL\n");
    }
    printf("\n");
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph)
{
     if (graph == NULL) {
        printf("Error with the graph.\n"); // Error message
        return;
    }

    // Free the existing adjacency list
    for (int i = 0; i < graph->numVertices; i++) {
        Node *current = graph->adjList[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        graph->adjList[i] = NULL; // Reset the adjacency list
    } // 

    // Create the adjacency list
    for (int i = 0; i < graph->numVertices; i++) {
        Node *tail = NULL;
        for (int j = 0; j < graph->numVertices; j++) {
            if (graph->adjMatrix[i][j] != 0) {
                Node *newNode = createNode(j); // Create a new node
                if (!graph->adjList[i]) {
                    graph->adjList[i] = newNode; // Set the head of the list
                    tail = newNode;
                } else {
                    tail->next = newNode; // Add the new node to the end of the list
                    tail = newNode;
                }
            }
        }
    }
}

/**
 * Performs Breadth-First Search (BFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which BFS starts (0-based index).
 */
void bfs(Graph *graph, int startVertex)
{
    if (graph == NULL) {
        printf("Error with the graph.\n"); // Error message
        return;
    }

    // Initialize the visited array and the queue
    int numVertices = graph->numVertices;
    int visited[numVertices];
    int queue[numVertices];

    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }

    int front = 0, rear = 0;

    if (startVertex < 0 || startVertex >= numVertices) {
        fprintf(stderr, "Error: Invalid start vertex.\n");
        return;
    }

    // Perform BFS
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    // Traverse the graph
    while (front != rear) {
        int currentVertex = queue[front++];

        printf("%d ", currentVertex + 1);

        Node *adjList = graph->adjList[currentVertex]; // Get the adjacency list of the current vertex
        while (adjList != NULL) {
            int adjVertex = adjList->vertex; // Get the adjacent vertex
            if (!visited[adjVertex]) {  // Check if the vertex has been visited
                visited[adjVertex] = 1; // Mark the vertex as visited
                queue[rear++] = adjVertex;
            }
            adjList = adjList->next; // Move to the next adjacent vertex
        } 
    }
    printf("\n");
}

/**
 * Performs Depth-First Search (DFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which DFS starts (0-based index).
 */
void dfs(Graph *graph, int startVertex)
{
    // Check if the graph is NULL
    if (graph == NULL) {
        printf("Error with the graph.\n"); // Error message
        return;
    }

    // Get the number of vertices in the graph
    int numVertices = graph->numVertices;

    // Validate the start vertex
    if (startVertex < 0 || startVertex >= numVertices) {
        fprintf(stderr, "Error: Invalid start vertex.\n"); // Error message
        return;
    }

    // Initialize the visited array to track visited vertices
    int visited[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }

    // Initialize a stack to perform iterative DFS
    int stack[numVertices];
    int top = -1;

    // Push the starting vertex onto the stack
    stack[++top] = startVertex;

    // Loop until the stack is empty
    while (top >= 0) {
        int currentVertex = stack[top--]; // Pop the top vertex

        // If the vertex has not been visited, mark it as visited
        if (!visited[currentVertex]) {
            printf("%d ", currentVertex + 1); // Print the vertex (1-based index)
            visited[currentVertex] = 1;
        }

        // Get the adjacency list of the current vertex
        Node *adjList = graph->adjList[currentVertex];
        int neighbors[numVertices];
        int neighborCount = 0;

        // Collect all unvisited neighbors
        while (adjList != NULL) {
            int adjVertex = adjList->vertex;
            if (!visited[adjVertex]) {
                neighbors[neighborCount++] = adjVertex;
            }
            adjList = adjList->next;
        }

        // Push neighbors onto the stack in reverse order
        for (int i = neighborCount - 1; i >= 0; i--) {
            stack[++top] = neighbors[i];
        }
    }

    printf("\n"); // Print a newline after traversal
}

/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex)
{
    // Check if the graph is NULL
    if (graph == NULL) {
        printf("Error with the graph.\n"); // Error message
        return;
    }

    // Get the number of vertices in the graph
    int numVertices = graph->numVertices;

    // Validate the start vertex
    if (startVertex < 0 || startVertex >= numVertices) {
        fprintf(stderr, "Error: Invalid start vertex.\n"); // Error message
        return;
    }

    // Arrays to store distances and visited status
    int distance[MAX_VERTICES]; // Stores the shortest distances from startVertex
    int visited[MAX_VERTICES]; // Tracks visited vertices

    // Initialize all distances to infinity and visited status to false
    for (int i = 0; i < numVertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance to the start vertex is 0
    distance[startVertex] = 0;

    // Loop to process all vertices
    for (int count = 0; count < numVertices - 1; count++) {
        int minDistance = INT_MAX;
        int minIndex = -1;

        // Find the unvisited vertex with the smallest distance
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i] && distance[i] <= minDistance) {
                minDistance = distance[i]; // Update the minimum distance
                minIndex = i;
            }
        }

        int u = minIndex; // Vertex with the smallest distance
        visited[u] = 1;   // Mark the vertex as visited

        // Update distances of adjacent vertices
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i] && graph->adjMatrix[u][i] != 0 && distance[u] != INT_MAX &&
                distance[u] + graph->adjMatrix[u][i] < distance[i]) { 
                distance[i] = distance[u] + graph->adjMatrix[u][i]; // Update the distance
            }
        }
    }

    // Print the shortest distances from the start vertex
    for (int i = 0; i < numVertices; i++) {
        printf("Shortest distance from vertex %d to vertex %d: ", startVertex + 1, i + 1);
        if (distance[i] == INT_MAX) {
            printf("Infinity\n"); // Vertex is unreachable
        } else {
            printf("%d\n", distance[i]); // Print the distance
        }
    }
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    if (graph == NULL) {
        printf("Error with the graph.\n"); // Error message
        return;
    }

    // Free the adjacency list
    for (int i = 0; i < graph->numVertices; i++) {
        Node *current = graph->adjList[i]; // Get the adjacency list of the vertex
        while (current) {
            Node *temp = current;
            current = current->next; //
            free(temp); // Free the node
            
        }
    }

    free(graph); // Free the graph structure
}

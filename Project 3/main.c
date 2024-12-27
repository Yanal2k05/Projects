#include "graph.h"

/*
 * A basic menu based structure has been provided
 */

int main(int argc, char *argv[]) {

    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Read the graph from the file
    Graph *graph = readGraph(argv[1]);
    if (graph == NULL) 
    {
        return 1; // Exit if the graph couldn't be read
    }

    // Create the adjacency list from the adjacency matrix
      createAdjacencyList(graph);

    int choice;
    // int startVertex = 1;

    do 
    {
        // Display menu options
        prompt();

        // Get user input
        printf("Enter your choice: ");
            if (scanf("%d", &choice) != 1) {
            // Clear input buffer and prompt again
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');  // Clear the buffer
            continue;
        }


        /*
         * You will need to add all the cases here.
         * Call the relevant functions in each case.
         * Make sure to handle invalid inputs or edge cases.
         */
         
        switch (choice) {
            case 1:
                // Display the adjacency list
                printf("Adjacency List:\n");
                displayAdjacencyList(graph);
                break;

            case 2:
                // Perform BFS starting from vertex 1 (index 0)
                printf("Final BFS Order:\n");
                bfs(graph, 0);  // Vertex 1 is at index 0
                break;

            case 3:
                // Perform DFS starting from vertex 1 (index 0)
                printf("Final DFS Order:\n");
                dfs(graph, 0);  // Vertex 1 is at index 0
                break;

            case 4:
                // Find shortest path using Dijkstra's algorithm
                dijkstra(graph, 0);  // Vertex 1 is at index 0
                break;

            case 5:
                // Exit the program
                printf("Exiting...\n");
                freeGraph(graph);
                return 0;

            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    } while (true);

    // Free the allocated memory for the graph
    freeGraph(graph);

    return 0;
}




#include "givenA1.h"

int main() {

    struct Animal dataZoo[NUM_SAMPLES]; 
    struct Animal testData[NUM_TEST_DATA];

    float mean = 0.0f;
    int mode = 0;
    int whichFeature;
    char fileName[30] = "a1Data.txt";
    int result = readFromFile(fileName, dataZoo);
    int newSample[NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 4, 1, 0, 1};
    int k, whichDistanceFunction;
    int kNearestNeighbors[NUM_SAMPLES];
    int neighborsForNewSample[NUM_SAMPLES];
    int choice; 
    int firstExecuted = 0; 
    int vector1[NUM_FEATURES];
    int vector2[NUM_FEATURES];

    while (1) {
        // Menu options display
        printf("Menu:\n");
        printf("1. Task 1: read file\n");
        printf("2. Task 2: find mean and mode\n");
        printf("3. Task 3: Display class distribution\n");
        printf("4. Task 4: Calculate Euclidean distance\n");
        printf("5. Task 5: Calculate Hamming distance\n");
        printf("6. Task 6: Calculate Jaccard similarity\n");
        printf("7. Task 7: Find k nearest neighbors\n");
        printf("8. Task 8: Predict class for a new sample\n");
        printf("9. Task 9: find the accuracy\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Check for invalid choice
        if (choice < 1 || choice > 9) {
            printf("Exiting program.\n");
            break; // Exit loop if choice is not 1-9
        }

        // check if task 1 is executed 
        if (choice != 1 && !firstExecuted) {
            printf("Task 1 must be executed first.\n");
            continue; 
        }

        switch (choice) {
            case 1:
                // Task 1: Read from file
                if (result == 1) {
                    printf("File read successfully.\n");
                } else {
                    printf("Error reading file.\n");
                }
                firstExecuted = 1; // Mark first task as executed
                break;

            case 2:
                // Task 2: Find mean and mode of a feature
                printf("Enter which feature you want (1 to %d): ", NUM_FEATURES);
                scanf("%d", &whichFeature);
                int Sfeature = generateStatisticsFeatureX(dataZoo, whichFeature, &mean, &mode);

                if (Sfeature == -1) {
                    printf("Invalid feature number.\n");
                } else {
                    printf("Mean of feature %d: %.2f\n", whichFeature, mean);
                    printf("Mode of feature %d: %d\n", whichFeature, mode);
                }
                break;

            case 3:
                // Task 3: Display class distribution
                classDistribution(dataZoo);
                break;

            case 4:
                // Task 4: Calculate Euclidean distance
                {
                    // Input for vector1
                    printf("Enter %d elements for vector1: ", NUM_FEATURES);
                    for (int i = 0; i < NUM_FEATURES; i++) {
                    scanf("%d", &vector1[i]);
                    }

                    // Input for vector2
                    printf("Enter %d elements for vector2: ", NUM_FEATURES);
                    for (int i = 0; i < NUM_FEATURES; i++) {
                    scanf("%d", &vector2[i]);
                    }

                    float distance = euclideanDistance(vector1, vector2);
                    printf("Euclidean Distance: %.2f\n", distance);
                }
                break;

            case 5:
                // Task 5: Calculate Hamming distance
                {
                    // Input for vector1
                    printf("Enter %d elements for vector1: ", NUM_FEATURES);
                    for (int i = 0; i < NUM_FEATURES; i++) {
                    scanf("%d", &vector1[i]);
                    }


                    // Input for vector2
                    printf("Enter %d elements for vector2: ", NUM_FEATURES);
                    for (int i = 0; i < NUM_FEATURES; i++) {
                    scanf("%d", &vector2[i]);
                    }
            
                    int difference = hammingDistance(vector1, vector2);
                    printf("Hamming Distance: %d\n", difference);
                }
                break;

            case 6:
                // Task 6: Calculate Jaccard similarity
                {
                    // Input for vector1
                    printf("Enter %d elements for vector1: ", NUM_FEATURES);
                    for (int i = 0; i < NUM_FEATURES; i++) {
                    scanf("%d", &vector1[i]);
                    }

                    // Input for vector2
                    printf("Enter %d elements for vector2: ", NUM_FEATURES);
                    for (int i = 0; i < NUM_FEATURES; i++) {
                    scanf("%d", &vector2[i]);
                    }
            
                    float similarity = jaccardSimilarity(vector1, vector2);
                    printf("Jaccard Similarity: %.2f\n", similarity);
                }
                break;

            case 7:
                // Task 7: Find k nearest neighbors based on the selected distance function
                printf("Enter the value of k: ");
                scanf("%d", &k);
                printf("Enter the distance function index (1 for Euclidean, 2 for Hamming, 3 for Jaccard's): ");
                scanf("%d", &whichDistanceFunction);

                findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, kNearestNeighbors);
                printf("Indices of the %d nearest neighbors:\n", k);
                for (int i = 0; i < k; i++) {
                    printf("Sample NearestNeighbors: %d\n", kNearestNeighbors[i]);
                    neighborsForNewSample[i] = kNearestNeighbors[i];
                }
                break;

            case 8:
                // Task 8: Predict class for a new sample using k nearest neighbors
                {
                    int predict = predictClass(dataZoo, neighborsForNewSample, k);
                    printf("\nThe predicted class for the new sample is %d.\n\n", predict);
                }
                break;

            case 9:
                // Task 9: Find the accuracy of your k nearest neighbors implementation
                {
                    char TestfileName[30] = "testData.csv";
                    FILE *Testfile = fopen(TestfileName, "r"); // Open the test data file for reading
                    if (Testfile == NULL) {
                        printf("Error reading file.\n"); // File couldn't be opened
                        break; // Exit the case
                    }

                    // Read and store test data from file
                    for (int i = 0; i < NUM_TEST_DATA; i++) {
                        // Read the animal's name and features
                        if (fscanf(Testfile, "%29[^,],", testData[i].animalName) != 1) {
                            fclose(Testfile); // Close the file
                            printf("Error reading file.\n"); // Failed to read
                            break; // Exit the loop and case
                        }

                        for (int j = 0; j < NUM_FEATURES; j++) {
                            if (fscanf(Testfile, "%d,", &testData[i].features[j]) != 1) {
                                fclose(Testfile); // Close the file
                                printf("Error reading file.\n"); // Failed to read a feature
                                break; // Exit the loop and case
                            }
                        }

                        // Read the class label for the animal
                        if (fscanf(Testfile, "%d", &testData[i].classLabel) != 1) {
                            fclose(Testfile); // Close the file
                            printf("Error reading file.\n"); // Failed to read the class label
                            break; // Exit the loop and case
                        }
                    }

                    fclose(Testfile); // Close the file after all data is read
                    printf("Test File read successfully.\n");

                    printf("Enter the value of k: ");
                    scanf("%d", &k);

                    // Calculate and print the accuracy
                    printf("Accuracy: %.2f%% \n", findAccuracy(dataZoo, testData, k) * 100);
                }
                break;

            default:
                printf("Invalid choice. Exiting program.\n");
                exit(1); // Exit the program with an error code
        }
    }
    return 0; 
    }

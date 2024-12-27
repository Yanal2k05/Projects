#include "givenA1.h"

// Function 1: Read animal data from a file
int readFromFile(char fName[30], struct Animal dataZoo[NUM_SAMPLES]) {
    FILE *file = fopen(fName, "r");
    if (file == NULL) {
        return -1; // File couldn't be opened
    }

        for (int i = 0; i < NUM_SAMPLES; i++) {
        // Read the animal's name
         fscanf(file, "%s", dataZoo[i].animalName);
           
    
        // Read the 16 features
        for (int j = 0; j < 16; j++) {
            fscanf(file, "%d", &dataZoo[i].features[j]);
                
        }

        // Read the class label
        fscanf(file, "%d", &dataZoo[i].classLabel);
 }
        

    fclose(file);
    return 1; // Success
}

// Function 2: Generate statistics (mean and mode) for a given feature across all samples
int generateStatisticsFeatureX(struct Animal dataZoo[NUM_SAMPLES], int whichFeature, float *mean, int *mode) {
    if (whichFeature < 1 || whichFeature > NUM_FEATURES) {
        fprintf(stderr, "Error: Invalid feature number %d.\n", whichFeature);
        return -1; 
    }

    int feature = whichFeature - 1;
    int sum = 0;
    int frequency[NUM_FEATURES]; 
    int maxFrequency = 0;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        int value = dataZoo[i].features[feature];
        sum += value;
        frequency[value]++;

        if (frequency[value] > maxFrequency) {
            maxFrequency = frequency[value];
            *mode = value;
        }
    }

    *mean = (float)sum / NUM_SAMPLES;
    return 0; 
}

// Function 3: Print class distribution as a histogram
void classDistribution(struct Animal dataZoo[NUM_SAMPLES]) {
    int classCounts[NUM_CLASSES] = {0};
    int height = 0;

    // Count the frequency of each class
    for (int i = 0; i < NUM_SAMPLES; i++) {
        if (dataZoo[i].classLabel >= 1 && dataZoo[i].classLabel <= NUM_CLASSES) {
            int index = dataZoo[i].classLabel - 1;
            classCounts[index]++;
           
           //height of the histogram
            if (classCounts[index] > height) {
                height = classCounts[index];
            }
        }
    }

    printf("\n");

    // Print the histogram by descending count
    for (int count = height; count > 0; count--) {
        for (int i = 0; i < NUM_CLASSES; i++) {
            if (classCounts[i] >= count) {
                if (classCounts[i] == count) {
                    printf("  (%d)\t\t", classCounts[i]); // Print the counts for each class
                } else {
                    printf("   *\t\t");
                }
            } else {
                printf(" \t\t");
            }
        }
        printf("\n");
    }

     // Print last row of the histogram
    for (int i = 0; i < NUM_CLASSES; i++) {
        printf("   *\t\t");
    }

    printf("\n");

    // Print the class labels below the histogram
    for (int i = 0; i < NUM_CLASSES; i++) {
        printf("Class %d\t\t", i + 1);
    }
    printf("\n");
}

// Function 4: Compute the Euclidean distance between two feature vectors
float euclideanDistance(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]) {
    float sum = 0.0;
    for (int i = 0; i < NUM_FEATURES; i++) {
        sum += pow(vector1[i] - vector2[i], 2);
    }
    return sqrt(sum);
}

// Function 5: Compute the Hamming distance between two feature vectors
int hammingDistance(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]) {
    int count = 0;
    for (int i = 0; i < NUM_FEATURES; i++) {
        if (vector1[i] != vector2[i]) count++;
    }
    return count;
}

// Function 6: Compute the Jaccard similarity between two feature vectors
float jaccardSimilarity(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]) {
    int same1 = 0, same0 = 0;
    for (int i = 0; i < NUM_FEATURES; i++) {
        if (vector1[i] == 1 && vector2[i] == 1) same1++;
        if (vector1[i] == 0 && vector2[i] == 0) same0++;
    }
    
    return (float)same1 / (float)(NUM_FEATURES - same0);
}

// function 7:
// the code for a sorting function is provided by chatgpt
 void findKNearestNeighbors(struct Animal dataZoo[NUM_SAMPLES], int newSample[NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors[NUM_SAMPLES]) {
    
    float distances[NUM_SAMPLES];
    int indices[NUM_SAMPLES]={0};
    int i, j;
    
    for (i = 0; i < NUM_SAMPLES; i++) {
        kNearestNeighbors[i] = 0;
       
    }

    // Calculate distances from newSample to all samples in dataZoo
    for (i = 0; i < NUM_SAMPLES; i++) {

        // Calculate distance based on the specified function
        if (whichDistanceFunction == 1) {
                                            // selection for euclidean distance
    distances[i] = euclideanDistance(dataZoo[i].features, newSample); 
    
} else if (whichDistanceFunction == 2) {
                                            // selection for hamming distance
    distances[i] = hammingDistance(dataZoo[i].features, newSample); 
} else if (whichDistanceFunction == 3) {
                                            // selection for jaccard distance
    distances[i] = /*1 - */ jaccardSimilarity(dataZoo[i].features, newSample); 

} else {

    printf("Invalid distance function index.\n");
    return;
}

        // Store the indices
        indices[i] = i;

    }

    // Sort the distances and their corresponding indices
    for (i = 0; i < NUM_SAMPLES - 1; i++) {
        for (j = i + 1; j < NUM_SAMPLES; j++) {
            if (distances[i] > distances[j]) {
                
                // Swap distance
                float tempDistance = distances[i];
                distances[i] = distances[j];
                distances[j] = tempDistance;
                
                // Swap corresponding indices
                int tempIndices = indices[i];
                indices[i] = indices[j];
                indices[j] = tempIndices;
            }
        }
    }

    // Store the first K indices
    for (i = 0; i < k; i++) {
        kNearestNeighbors[i] = indices[i];
    }
    for (i = 0; i < NUM_SAMPLES; i++) {
  
    }  
 }


// function 8: 
int predictClass (struct Animal dataZoo [NUM_SAMPLES], int neighborsForNewSample [NUM_SAMPLES], int k){
  
    
    // Array to count votes for each class
    int votes[NUM_CLASSES] = {0}; // Adjust NUM_CLASSES as per your data

    // Accumulate votes based on the class of each neighbor
    for (int i = 0; i < k; i++) {
        int neighborIndex = neighborsForNewSample[i];
        votes[dataZoo[neighborIndex].classLabel]++; // Assuming class labels start from 1
    }

    // Determine the class with the most votes
    int maxVotes = 0, predictedClass = -1;
    for (int i = 0; i < NUM_CLASSES; i++) {
        if (votes[i] > maxVotes) {
            maxVotes = votes[i];
            predictedClass = i; // Adjusting index to class label
        }
    }
       printf("Predicted class: %d\n", predictedClass);

    return predictedClass; // Return the predicted class for the new sample
} 

// function 9:
float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], struct Animal testData [NUM_TEST_DATA], int k){
    float correct = 0;
    int whichDistanceFunction;
    int kNearestNeighbors[NUM_SAMPLES];
    
   
    printf("Enter the distance function index (1 for Euclidean, 2 for Hamming, 3 for Jaccard's): ");
    scanf("%d", &whichDistanceFunction);

    for (int i = 0; i < NUM_TEST_DATA; i++) {
    // Find k-nearest neighbors of the current test sample using the chosen distance function.
        findKNearestNeighbors(dataZoo, testData[i].features, k, whichDistanceFunction, kNearestNeighbors);

        // Predict the class of the test sample
        int predict = predictClass(dataZoo, kNearestNeighbors, k);

        // If the prediction matches the actual class label, increment the correct counter.
        if (predict == testData[i].classLabel) correct++;
    }
    
     // Calculate and return the accuracy 
    return correct/(float) NUM_TEST_DATA;
} 


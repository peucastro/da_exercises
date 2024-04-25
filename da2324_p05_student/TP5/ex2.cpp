#include "exercises.h"

unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    // Allocate memory for the Dynamic Programming table
    unsigned int maxValue[100][101];

    // Step 1: initialize the table (base cases)
    // Base case k > 0 && i = 0
    for (unsigned int k = 0; k <= maxWeight; k++) {
        if (k >= weights[0])
            maxValue[0][k] = values[0];
        else
            maxValue[0][k] = 0;
    }
    // Base case k = 0
    for (unsigned int i = 1; i <= n; i++)
        maxValue[i][0] = 0;

    // Step 2: Iterate through all items
    for (unsigned int i = 1; i < n; i++) {
        for (unsigned int k = 1; k <= maxWeight; k++) {
            // Item i doesn't fit in the Knapsack
            if (k < weights[i])
                maxValue[i][k] = maxValue[i - 1][k];
                // Item i fits, but it's necessary to check if it improves the solution
            else {
                unsigned aux = values[i] + maxValue[i - 1][k - weights[i]];
                if (aux >= maxValue[i - 1][k])    // Include the item (improves the solution)
                    maxValue[i][k] = aux;
                else
                    maxValue[i][k] = maxValue[i - 1][k]; // Don't include the item (doesn't improve the solution)
            }
        }
    }

    // Step3: Construct the solution
    for (unsigned int i = 0; i < n; i++)
        usedItems[i] = false;

    unsigned int remainingWeight = maxWeight;
    unsigned int currItem = n - 1;

    for (unsigned int i = n - 1; i > 0; i--) {
        if (remainingWeight == 0)
            break;

        if (maxValue[i][remainingWeight] != maxValue[i - 1][remainingWeight]) {
            usedItems[i] = true;
            remainingWeight -= weights[i];
            currItem--;
        }
    }
    if (remainingWeight > 0)
        usedItems[0] = true;

    return maxValue[n - 1][maxWeight];
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex2, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP5_Ex2, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}
// By: Gonçalo Leão

#include <vector>

unsigned int integerKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight,
                             bool usedItems[]) {
    unsigned int maxKnapsackValue = 0;
    std::vector<bool> currUsedItems(n);

    for (unsigned int i = 0; i < (1 << n); i++) {
        unsigned int currKnapsackWeight = 0;
        unsigned int currKnapsackValue = 0;

        for (unsigned int j = 0; j < n; j++) {
            currUsedItems[j] = false;

            if (i & (1 << j)) {
                currKnapsackValue += values[j];
                currKnapsackWeight += weights[j];
                currUsedItems[j] = true;
            }
        }

        if (currKnapsackValue > maxKnapsackValue && currKnapsackWeight <= maxWeight) {
            maxKnapsackValue = currKnapsackValue;
            for (unsigned int k = 0; k < n; k++) {
                usedItems[k] = currUsedItems[k];
            }
        }
    }

    return maxKnapsackValue;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP2_Ex3, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}
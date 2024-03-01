// By: Gonçalo Leão

#include <algorithm>

double fractionalKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight,
                          double usedItems[]) {
    std::pair<double, unsigned int> ratios[n];
    double knapsackWeight = 0.0;
    double knapsackValue = 0.0;

    for (unsigned int i = 0; i < n; i++)
        ratios[i] = {values[i] / weights[i], i};
    std::sort(ratios, ratios + n, [](std::pair<double, unsigned int> p1, std::pair<double, unsigned int> p2) -> bool {
        return p1.first > p2.first;
    });

    unsigned index, currValue, currWeight;
    for (unsigned int i = 0; i < n; i++) {
        index = ratios[i].second;
        currValue = values[index];
        currWeight = weights[index];

        if (knapsackWeight + currWeight <= maxWeight) {
            knapsackWeight += currWeight;
            knapsackValue += currValue;
            usedItems[index] = 1.0;
        } else {
            double frac = (maxWeight - knapsackWeight) / currWeight;
            knapsackWeight += currWeight * frac;
            knapsackValue += currValue * frac;
            usedItems[index] = frac;
            break;
        }
    }

    return knapsackValue;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex4, testFractionalKnapsack_3items) {
    const unsigned int n = 3;
    {
        unsigned int values[n] = {60, 100, 120};
        unsigned int weights[n] = {10, 20, 30};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsack(values, weights, n, 50, usedItems), 240.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 2.0 / 3.0, 0.00001);
    }
}

TEST(TP2_Ex4, testFractionalKnapsack_7items) {
    const unsigned int n = 7;
    {
        unsigned int values[n] = {10, 5, 15, 7, 6, 18, 3};
        unsigned int weights[n] = {2, 3, 5, 7, 1, 4, 1};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsack(values, weights, n, 15, usedItems), 52.0 + 10.0 / 3.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 2.0 / 3.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[3], 0.0, 0.00001);
        EXPECT_NEAR(usedItems[4], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[5], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[6], 1.0, 0.00001);
    }
}
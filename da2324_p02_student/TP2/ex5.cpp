// By: Gonçalo Leão

#include <vector>
#include <algorithm>

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    bool foundSol = false;
    unsigned int minCoins = 0;
    unsigned int currCand[n];

    for (unsigned int i = 0; i < n; i++)
        currCand[i] = 0;

    unsigned int k, totalValue, totalCoins, currIndex;
    while (true) {
        totalValue = 0;
        totalCoins = 0;

        for (k = 0; k < n; k++) {
            totalValue += C[k] * currCand[k];
            totalCoins += currCand[k];
        }

        if (totalValue == T) {
            if (!foundSol || totalCoins < minCoins) {
                minCoins = totalCoins;
                foundSol = true;

                for (k = 0; k < n; k++)
                    usedCoins[k] = currCand[k];
            }
        }

        currIndex = 0;
        while (currCand[currIndex] == Stock[currIndex]) {
            currIndex++;
            if (currIndex == n)
                break;
        }
        if (currIndex == n)
            break;

        for (k = 0; k < currIndex; k++)
            currCand[k] = 0;

        currCand[currIndex]++;
    }

    return foundSol;
}

bool changeMakingGR(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int remaining = T;
    std::pair<unsigned int, unsigned int> aux[n];

    for (unsigned int i = 0; i < n; i++)
        aux[i] = {C[i], i};
    std::sort(aux, aux + n,
              [](std::pair<unsigned int, unsigned int> p1, std::pair<unsigned int, unsigned int> p2) -> bool {
                  return p1.first > p2.first;
              });

    for (unsigned int i = 0; i < n; i++) {
        unsigned int index = aux[i].second;
        unsigned usedRatio = 0;

        if (remaining - C[index] >= 0) {
            usedRatio = remaining / C[index];
            if (usedRatio > Stock[index])
                usedRatio = Stock[index];
            remaining -= usedRatio * C[index];
        }

        usedCoins[index] = usedRatio;
    }

    return remaining == 0;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex5, hasBFChangeCanonical) {
    unsigned int C[] = {1, 2, 5, 10};
    unsigned int Stock[] = {1, 1, 1, 1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C, Stock, n, 13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1, 2, 4, 2};
    EXPECT_EQ(changeMakingBF(C, Stock2, n, 38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10, 2, 4, 2};
    EXPECT_EQ(changeMakingBF(C, Stock3, n, 10, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex5, hasBFChangeNonCanonical) {
    unsigned int C[] = {1, 4, 5};
    unsigned int Stock[] = {2, 2, 1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C, Stock, n, 6, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C, Stock, n, 8, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8, 2, 1};
    EXPECT_EQ(changeMakingBF(C, Stock2, n, 7, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C, Stock2, n, 8, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex5, hasNoBFChange) {
    unsigned int C[] = {1, 2, 5, 10};
    unsigned int Stock[] = {0, 1, 1, 1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C, Stock, n, 18, usedCoins), false);
    EXPECT_EQ(changeMakingBF(C, Stock, n, 1, usedCoins), false);
}

TEST(TP2_Ex5, hasGreedyChange) {
    unsigned int C[] = {1, 2, 5, 10};
    unsigned int Stock[] = {1, 1, 1, 1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1, 2, 4, 2};
    EXPECT_EQ(changeMakingGR(C, Stock2, n, 38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP2_Ex5, hasNoGreedyChange) {
    unsigned int C[] = {1, 2, 5, 10};
    unsigned int Stock[] = {0, 1, 1, 1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 18, usedCoins), false);
    EXPECT_EQ(changeMakingGR(C, Stock, n, 1, usedCoins), false);
}
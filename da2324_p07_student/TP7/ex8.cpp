// By: Gonçalo Leão

#include "exercises.h"
#include <climits>

void tspRec(const unsigned int **dists, unsigned int n, unsigned int curI, unsigned int curDist, unsigned int curPath[],
            unsigned int &minDist, unsigned int path[]) {

    if (curI == n) {
        curDist += dists[curPath[n - 1]][curPath[0]];
        if (curDist < minDist) {
            minDist = curDist;
            for (unsigned int i = 0; i < n; i++) {
                path[i] = curPath[i];
            }
        }
        return;
    } else {
        for (unsigned int i = 1; i < n; i++) {
            if (curDist + dists[curPath[curI - 1]][i] <= minDist) {
                bool isNewNode = true;
                for (int j = 1; j < curI; j++) {
                    if (curPath[j] == i) {
                        isNewNode = false;
                        break;
                    }
                }
                if (isNewNode) {
                    curPath[curI] = i;
                    tspRec(dists, n, curI + 1, curDist + dists[curPath[curI - 1]][curPath[curI]], curPath, minDist,
                           path);
                }
            }
        }
    }
}

unsigned int tspBT(const unsigned int **dists, unsigned int n, unsigned int path[]) {
    unsigned currPath[10000];
    unsigned int minDist = INT_MAX;
    currPath[0] = 0;

    tspRec(dists, n, 1, 0, currPath, minDist, path);

    return minDist;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP7_Ex8, testTSP_4x4_symmetric) {
    const unsigned int n = 4;
    const unsigned int dists[n][n] = {{0,  10, 15, 20},
                                      {10, 0,  35, 25},
                                      {15, 35, 0,  30},
                                      {20, 25, 30, 0}};

    // Convert 2D array to double pointer
    auto **ptr = new const unsigned int *[n];
    for (unsigned int i = 0; i < n; i++)
        ptr[i] = dists[i];
    unsigned int path[n];

    EXPECT_EQ(tspBT(ptr, n, path), 80);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 3);
    EXPECT_EQ(path[3], 2);
}

TEST(TP7_Ex8, testTSP_4x4_assymmetric) {
    const unsigned int n = 4;
    const unsigned int dists[n][n] = {{0, 10, 15, 20},
                                      {5, 0,  9,  10},
                                      {6, 13, 0,  12},
                                      {8, 8,  9,  0}};

    // Convert 2D array to double pointer
    auto **ptr = new const unsigned int *[n];
    for (unsigned int i = 0; i < n; i++)
        ptr[i] = dists[i];
    unsigned int path[n];

    EXPECT_EQ(tspBT(ptr, n, path), 35);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 3);
    EXPECT_EQ(path[3], 2);
}

TEST(TP7_Ex8, testTSP_5x5_symmetric) {
    const unsigned int n = 5;
    const unsigned int dists[n][n] = {{0,  12, 10, 19, 8},
                                      {12, 0,  3,  7,  2},
                                      {10, 3,  0,  6,  20},
                                      {19, 7,  6,  0,  4},
                                      {8,  2,  20, 4,  0}};

    // Convert 2D array to double pointer
    auto **ptr = new const unsigned int *[n];
    for (unsigned int i = 0; i < n; i++)
        ptr[i] = dists[i];
    unsigned int path[n];

    EXPECT_EQ(tspBT(ptr, n, path), 32);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 2);
    EXPECT_EQ(path[2], 1);
    EXPECT_EQ(path[3], 3);
    EXPECT_EQ(path[4], 4);
}
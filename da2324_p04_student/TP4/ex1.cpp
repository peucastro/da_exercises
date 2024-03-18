#include "exercises.h"
#include "cmath"

int maxSubsequence(int A[], int start, int finish, int &i, int &j) {
    if (start == finish) {
        i = start;
        j = finish;
        return A[start];
    }

    int middle2 = (int) (round((start + finish) / 2.0));
    int middle1 = middle2 - 1;
    int iLeft, jLeft, iRight, jRight;

    int sumLeft = maxSubsequence(A, start, middle1, iLeft, jLeft);
    int sumRight = maxSubsequence(A, middle2, finish, iRight, jRight);

    int currSum = A[middle1];
    int bestCrossSum1 = A[middle1];
    int bestCrossSumI = middle1;
    for (int k = middle1 - 1; k >= start; k--) {
        currSum += A[k];
        if (currSum > bestCrossSum1) {
            bestCrossSum1 = currSum;
            bestCrossSumI = k;
        }
    }

    currSum = A[middle2];
    int bestCrossSum2 = A[middle2];
    int bestCrossSumJ = middle2;
    for (int k = middle2 + 1; k <= finish; k++) {
        currSum += A[k];
        if (currSum > bestCrossSum2) {
            bestCrossSum2 = currSum;
            bestCrossSumJ = k;
        }
    }

    int bestCrossSum = bestCrossSum1 + bestCrossSum2;

    if (bestCrossSum > sumLeft && bestCrossSum > sumRight) {
        i = bestCrossSumI;
        j = bestCrossSumJ;
        return bestCrossSum;
    } else if (sumLeft > sumRight && sumLeft > bestCrossSum) {
        i = iLeft;
        j = jLeft;
        return sumLeft;
    } else if (sumRight > sumLeft && sumRight > bestCrossSum) {
        i = jRight;
        j = jRight;
        return sumRight;
    }
}

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    if (n == 0)
        return 0;
    else return maxSubsequence(A, 0, n - 1, i, j);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex1, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1, n1, i, j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2, n2, i, j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3, n3, i, j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4, n4, i, j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}
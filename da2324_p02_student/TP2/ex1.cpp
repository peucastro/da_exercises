// By: Gonçalo Leão
// With contributions by Eduardo Almeida

#include <climits>

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int maxSum = INT_MIN;
    int currSum;

    for (unsigned int x = 0; x < n; x++) {
        for (unsigned int y = x + 1; y < n; y++) {
            currSum = 0;

            for (unsigned w = x; w <= y; w++)
                currSum += A[w];

            if (currSum > maxSum) {
                i = x;
                j = y;
                maxSum = currSum;
            }
        }
    }

    return maxSum;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex1, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A, n, i, j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}
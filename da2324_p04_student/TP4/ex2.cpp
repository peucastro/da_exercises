#include <iostream>     // std::cout
#include <algorithm>    // std::count
#include "exercises.h"

std::string hanoiDC(unsigned int n, char src, char dest) {
    std::string moves;
    if (n == 1) {
        moves += src;
        moves += "->";
        moves += dest;
    } else {
        char aux = 'A' + 'B' + 'C' - src - dest;
        moves += hanoiDC(n - 1, src, aux) + ",";
        moves += src;
        moves += "->";
        moves += dest;
        moves += "," + hanoiDC(n - 1, aux, dest);
    }
    return moves;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, testHanoi_height4) {
    std::string moves = hanoiDC(4, 'A', 'B');
    EXPECT_EQ(std::count(moves.begin(), moves.end(), ','), 14); // there are 15 moves
    EXPECT_EQ(moves, "A->C,A->B,C->B,A->C,B->A,B->C,A->C,A->B,C->B,C->A,B->A,C->B,A->C,A->B,C->B");
}
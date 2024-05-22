#include "ortools/linear_solver/linear_solver.h"
#include "exercises.h"

using namespace operations_research;

bool checkInfeasible() {
    // TODO
}


#include <gtest/gtest.h>

TEST(TPLP_Ex3, InfeasibleTest) {
    EXPECT_TRUE(checkInfeasible());
}
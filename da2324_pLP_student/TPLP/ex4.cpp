#include "ortools/linear_solver/linear_solver.h"
#include "exercises.h"
#include "solution2vars.h"

using namespace operations_research;

LPSolution2Vars ex4() {
    // TODO
}

#include <gtest/gtest.h>

TEST(TPLP_Ex4, OptimalSolution) {
    LPSolution2Vars solution = ex4();

    ASSERT_EQ(solution.resultStatus, MPSolver::ResultStatus::OPTIMAL);

    EXPECT_DOUBLE_EQ(solution.x1, 12.0);
    EXPECT_DOUBLE_EQ(solution.x2, 8.0);
    EXPECT_DOUBLE_EQ(solution.objectiveValue, 316);
}
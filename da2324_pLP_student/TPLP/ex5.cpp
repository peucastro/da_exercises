#include "ortools/linear_solver/linear_solver.h"
#include "exercises.h"
#include "solution2vars.h"

using namespace operations_research;

LPSolution2Vars ex5() {
    // TODO
}

#include <gtest/gtest.h>

TEST(TPLP_Ex5, OptimalSolution) {
    LPSolution2Vars solution = ex5();

    ASSERT_EQ(solution.resultStatus, MPSolver::ResultStatus::OPTIMAL);

    EXPECT_DOUBLE_EQ(solution.x1, 0.0);
    EXPECT_DOUBLE_EQ(solution.x2, 0.0);
    EXPECT_DOUBLE_EQ(solution.objectiveValue, 0.0);
}
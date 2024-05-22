#include "ortools/linear_solver/linear_solver.h"
#include "exercises.h"
#include "solution3vars.h"

using namespace operations_research;

LPSolution3Vars ex1() {
    // TODO
}


#include <gtest/gtest.h>

TEST(TPLP_Ex1, OptimalSolution) {
    LPSolution3Vars solution = ex1();

    ASSERT_EQ(solution.resultStatus, MPSolver::ResultStatus::OPTIMAL);

    EXPECT_DOUBLE_EQ(solution.x1, 18.0);
    EXPECT_DOUBLE_EQ(solution.x2, 0.0);
    EXPECT_DOUBLE_EQ(solution.x3, 11.0);
    EXPECT_DOUBLE_EQ(solution.objectiveValue, 69.0);
}
#ifndef DA2324_PLP_SOL_SOLUTION3VARS_H
#define DA2324_PLP_SOL_SOLUTION3VARS_H
using namespace operations_research;

struct LPSolution3Vars {
    double x1 = 0.0;
    double x2 = 0.0;
    double x3 = 0.0;
    double objectiveValue = 0.0;
    MPSolver::ResultStatus resultStatus = MPSolver::NOT_SOLVED;
};
#endif //DA2324_PLP_SOL_SOLUTION3VARS_H

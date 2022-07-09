#ifndef ADAPATIVE_RK_H
#define ADAPATIVE_RK_H

#include "../constants/solver_constants.h"

SolverSolution *create_solver_solution(size_t n);
void free_solver_solution(SolverSolution *solution);

SolverSolution *adaptive_rk_solve(RKSolver *solver, double t0, double t1, double y0[VEC_SIZE], double tol, double h0);

#endif // ADAPATIVE_RK_H
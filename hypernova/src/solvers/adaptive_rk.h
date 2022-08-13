#ifndef ADAPATIVE_RK_H
#define ADAPATIVE_RK_H

#include "../abstractions/solver_abstractions.h"

void free_solver_solution(SolverSolution *solution);

SolverSolution *adaptive_rk_solve(RKSolver *solver, ODEFunction f, Problem *problem, double tol, double h0);
void adaptive_rk_step(ODEFunction f, RKSolver *solver, Spacecraft spacecraft,
                      double t, double jd, double y[VEC_SIZE], double h, double *e);

#endif // ADAPATIVE_RK_H
#ifndef ADAPATIVE_RK_H
#define ADAPATIVE_RK_H

#include "../constants/solver_abstractions.h"

void free_solver_solution(SolverSolution *solution);

SolverSolution *adaptive_rk_solve(RKSolver *solver, ODEFunction f,
                                  double t0, double t1, double y0[VEC_SIZE], double tol, double h0);
void adaptive_rk_step(ODEFunction f, RKSolver *solver,
                      double t, double jd, double y[VEC_SIZE], double h, double *e);

#endif // ADAPATIVE_RK_H
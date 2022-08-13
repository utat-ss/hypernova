#ifndef RK4_H
#define RK4_H

#include "../../abstractions/solver_abstractions.h"

void trivial_error_correlation_rk4(double h, double F[MAX_BUTCHER_TABLEAU_SIZE][VEC_SIZE], double *e);

RKSolver *rk4();

#endif
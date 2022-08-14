#ifndef SOLVER_ABSTRACTIONS_H
#define SOLVER_ABSTRACTIONS_H

#include <stdbool.h>
#include <stdlib.h>
#include "../constants/program_constants.h"
#include "spacecraft.h"

#define MAX_BUTCHER_TABLEAU_SIZE 25

typedef struct SolverSolution
{
    double *t;             // mission elapsed time in seconds
    double *jd;            // absolute mission time in jd
    double (*y)[VEC_SIZE]; // position and velocity of spacecraft
    size_t n;              // number of steps taken
} SolverSolution;

typedef struct ButcherTableau
{
    const double (*A)[MAX_BUTCHER_TABLEAU_SIZE]; // Derivative weights
    const double(*b);                            // Next step weights
    const double(*c);                            // Evaluation positions
} ButcherTableau;

typedef struct SymplecticSolver
{
    // Weights
    const double(*c);
    const double(*d);
    const size_t num_stages;
} SymplecticSolver;

// typedef for ode function
typedef void (*ODEFunction)(double t, double jd, double y[VEC_SIZE], double dydt[VEC_SIZE], Spacecraft spacecraft);

// typedef for error correlation
typedef double (*RKErrorCorrelation)(double h, double F[MAX_BUTCHER_TABLEAU_SIZE][VEC_SIZE]);

typedef struct RKSolver
{
    const ButcherTableau weights;
    RKErrorCorrelation err_corr;
    const bool is_adaptive;
    const size_t num_stages;
    const size_t order;
} RKSolver;

typedef struct Problem
{
    double t0;
    double t1;
    Spacecraft spacecraft;
    double y0[VEC_SIZE];
} Problem;

void free_solver_solution(SolverSolution *solution);

#endif
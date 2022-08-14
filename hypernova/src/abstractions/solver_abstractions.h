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
    double (*A)[MAX_BUTCHER_TABLEAU_SIZE]; // Derivative weights
    double(*b);                            // Next step weights
    double(*c);                            // Evaluation positions
} ButcherTableau;

typedef struct SymplecticSolver
{
    // Weights
    double(*c);
    double(*d);
    size_t num_stages;
} SymplecticSolver;

// typedef for ode function
typedef void (*ODEFunction)(double t, double jd, double y[VEC_SIZE], double dydt[VEC_SIZE], Spacecraft spacecraft);

// typedef for error correlation
typedef double (*RKErrorCorrelation)(double h, double F[MAX_BUTCHER_TABLEAU_SIZE][VEC_SIZE]);

typedef struct RKSolver
{
    ButcherTableau weights;
    RKErrorCorrelation err_corr;
    bool is_adaptive;
    size_t num_stages;
    size_t order;
} RKSolver;

typedef union Solver
{
    RKSolver rk;
    SymplecticSolver symplectic;
} Solver;

enum SolverType
{
    RK,
    SYMPLECTIC
};

typedef struct Problem
{
    double t0;
    double t1;
    Spacecraft spacecraft;
    double y0[VEC_SIZE];
} Problem;

void free_solver_solution(SolverSolution *solution);
Solver cast_to_solver(void *solver);

#endif
#ifndef SOLVER_ABSTRACTIONS_H
#define SOLVER_ABSTRACTIONS_H

#include <stdbool.h>
#include <stdlib.h>

#define VEC_SIZE 6
#define MAX_BUTCHER_TABLEAU_SIZE 25

typedef struct SolverSolution
{
    double *t;             // mission elapsed time in seconds
    double *jd;            // absolute mission time in jd
    double (*y)[VEC_SIZE]; // position and velocity of spacecraft
    size_t n;                 // number of steps taken
} SolverSolution;

typedef struct ButcherTableau
{
    const double (*A)[MAX_BUTCHER_TABLEAU_SIZE];
    const double(*b);
    const double(*c);
} ButcherTableau;

// typedef for ode function
typedef void (*ODEFunction)(double t, double jd, double y[VEC_SIZE], double dydt[VEC_SIZE]);

// typedef for error correlation
typedef void (*RKErrorCorrelation)(double h, double F[MAX_BUTCHER_TABLEAU_SIZE][VEC_SIZE], double *e);

typedef struct RKSolver
{
    ButcherTableau *weights;
    RKErrorCorrelation err_corr;
    const bool is_adaptive;
    const size_t num_stages;
    const size_t order;
} RKSolver;


#endif
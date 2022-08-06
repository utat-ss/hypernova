#ifndef SOLVER_CONSTANTS_H
#define SOLVER_CONSTANTS_H

#define VEC_SIZE 6
#define MAX_BUTCHER_TABLEAU_SIZE 25

typedef struct SolverSolution
{
    double *t;             // mission elapsed time in seconds
    double *jd;            // absolute mission time in jd
    double (*y)[VEC_SIZE]; // position and velocity of spacecraft
    int n;              // number of steps taken
} SolverSolution;

typedef struct ButcherTableau
{
    double (*A)[MAX_BUTCHER_TABLEAU_SIZE];
    double(*b);
    double(*c);
} ButcherTableau;
typedef struct RKSolver
{
    ButcherTableau *weights;
    int num_stages;
    int order;
} RKSolver;

// typedef for ode function
typedef void (*ODEFunction)(double t, double jd, double y[VEC_SIZE], double dydt[VEC_SIZE]);

// typedef for error correlation
typedef void (*RKErrorCorrelation)(double h, double F[MAX_BUTCHER_TABLEAU_SIZE][VEC_SIZE], double *e);

#endif
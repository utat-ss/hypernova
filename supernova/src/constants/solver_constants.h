#ifndef SOLVER_CONSTANTS_H
#define SOLVER_CONSTANTS_H

#define VEC_SIZE 6

typedef struct SolverSolution
{
    double *t;             // mission elapsed time in seconds
    double *jd;            // absolute mission time in jd
    double (*y)[VEC_SIZE]; // position and velocity of spacecraft
    size_t n;              // number of steps taken
} SolverSolution;

typedef struct ButcherTableau
{
    double A[][];
    double b[];
    double c[];
} ButcherTableau;
typedef struct RKSolver
{
    ButcherTableau *weights;
    size_t num_stages;
} RKSolver;

#endif
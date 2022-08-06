#include "adaptive_rk.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

SolverSolution *adaptive_rk_solve(RKSolver *solver, ODEFunction f, RKErrorCorrelation err_corr,
                                  double t0, double t1, double y0[VEC_SIZE], double tol, double h0)
{
    /*
     * Solve the ODE y' = f(t, y) from t0 to t1 using an adaptive Runge-Kutta method.
     *
     * solver: the RKSolver to use
     * f: the ODE function to solve
     * err_corr: the error correlation function to use
     * t0: the initial time, in jd
     * t1: the final time, in jd
     * y0: the initial state
     * tol: the desired error tolerance
     * h0: the initial step size
     *
     * Returns a SolverSolution struct containing the solution.
     */

    // Check for invalid inputs
    if (t0 > t1)
    {
        fprintf(stderr, "Error: t0 > t1\n");
        return NULL;
    }

    if (tol < 0)
    {
        fprintf(stderr, "Error: tol < 0\n");
        return NULL;
    }

    if (h0 <= 0)
    {
        fprintf(stderr, "Error: h0 <= 0\n");
        return NULL;
    }
    // Estimate number of steps required
    int n = (int)fmax(ceil((t1 - t0) * 86400 / h0), 10);
    int step = 0;

    // Initialize the solution struct
    SolverSolution *solution = malloc(sizeof(SolverSolution));
    solution->t = malloc(n * sizeof(double));
    solution->jd = malloc(n * sizeof(double));
    solution->y = malloc(n * sizeof(double[VEC_SIZE]));

    // Initialize step variables
    double h = h0;
    double h_old = h0;

    double t = 0;       // elapsed time, in seconds
    double jd = t0;     // absolute mission time, in jd
    double y[VEC_SIZE]; // current state
    double e;

    // Initialize the solution vector
    for (int i = 0; i < VEC_SIZE; i++)
    {
        solution->y[0][i] = y0[i];
        y[i] = y0[i];
    }
    solution->t[0] = t;
    solution->jd[0] = jd;

    // RK loop
    while (jd - h/86400 < t1)
    {
        adaptive_rk_step(f, solver, err_corr, t, jd, y, h, &e);

        // accept step (hardcoded for now)

        // double size of array and reallocate memory
        if ((step + 1) >= n)
        {
            n *= 2;
            solution->y = (double(*)[6])realloc(solution->y, n * sizeof(double[VEC_SIZE]));
            solution->t = (double(*))realloc(solution->t, n * sizeof(double));
            solution->jd = (double(*))realloc(solution->jd, n * sizeof(double));
        }
        for (int i = 0; i < VEC_SIZE; i++)
        {
            solution->y[step + 1][i] = y[i];
        }
        solution->t[step + 1] = t + h;
        solution->jd[step + 1] = jd + h / 86400;

        step++;
        t += h;
        jd += h / 86400;

        // prevent solver from overstepping the end of the mission
        // if (jd + h / 86400 > t1)
        // {
        //     h = (t1 - jd) * 86400;
        // }
    }
    solution->n = step;

    return solution;
}

void adaptive_rk_step(ODEFunction f, RKSolver *solver, RKErrorCorrelation err_corr,
                      double t, double jd, double y[VEC_SIZE], double h, double *e)
{
    double F[MAX_BUTCHER_TABLEAU_SIZE][VEC_SIZE]; // slopes at each stage
    double v[VEC_SIZE];                           // intermediate values at each stage

    // perform all stages
    for (int stage = 0; stage < solver->num_stages; stage++)
    {
        for (int component = 0; component < VEC_SIZE; component++)
        {
            v[component] = y[component];
            for (int i = 0; i < stage; i++)
            {
                v[component] += h * F[i][component] * solver->weights->A[stage][i];
            }
        }
        f(t + h * solver->weights->c[stage], jd + (h * solver->weights->c[stage]) / 86400, v, F[stage]);
    }

    err_corr(h, F, e);

    for (int component = 0; component < VEC_SIZE; component++)
    {
        for (int stage = 0; stage < solver->num_stages; stage++)
        {
            y[component] += h * F[stage][component] * solver->weights->b[stage];
        }
    }
}

void free_solver_solution(SolverSolution *solution)
{
    free(solution->t);
    free(solution->jd);
    free(solution->y);
    free(solution);
}

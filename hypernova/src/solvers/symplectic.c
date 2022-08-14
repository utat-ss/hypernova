#include "symplectic.h"

#include <math.h>
#include <stdio.h>

SolverSolution *symplectic_solve(SymplecticSolver solver, ODEFunction f, Problem problem, double h)
{
    // Check for invalid inputs
    if (problem.t0 > problem.t1)
    {
        fprintf(stderr, "Error: t0 > t1\n");
        return NULL;
    }

    if (h <= 0)
    {
        fprintf(stderr, "Error: h0 <= 0\n");
        return NULL;
    }

    // Determine number of steps required
    size_t n = (size_t)ceil((problem.t1 - problem.t0) * 86400 / h);

    SolverSolution *solution = malloc(sizeof(SolverSolution));
    solution->t = malloc(n * sizeof(double));
    solution->jd = malloc(n * sizeof(double));
    solution->y = malloc(n * sizeof(double[VEC_SIZE]));
    solution->n = n;

    // Initialize step variables
    double t = 0;           // elapsed time, in seconds
    double jd = problem.t0; // absolute mission time, in jd
    double y[VEC_SIZE];     // current state
    double a[VEC_SIZE];     // acceleration

    // Initialize the solution vector
    for (size_t i = 0; i < VEC_SIZE; i++)
    {
        solution->y[0][i] = problem.y0[i];
        y[i] = problem.y0[i];
    }
    solution->t[0] = t;
    solution->jd[0] = jd;

    // Run solver
    for (size_t step = 1; step < n; step++)
    {
        for (size_t stage = 0; stage < solver.num_stages; stage++)
        {
            // update position
            for (size_t j = 0; j < 3; j++)
            {
                y[j] += solver.c[stage] * y[j + 3] * h;
            }

            // Compute acceleration
            f(t, jd, y, a, problem.spacecraft);

            // update velocity
            for (size_t j = 0; j < 3; j++)
            {
                y[j + 3] += solver.d[stage] * a[j + 3] * h;
            }
        }

        // Update solution, time, jd
        t += h;
        jd += h / 86400;
        for (size_t i = 0; i < VEC_SIZE; i++)
        {
            solution->y[step][i] = y[i];
        }
        solution->t[step] = t;
        solution->jd[step] = jd;
    }
    return solution;
}
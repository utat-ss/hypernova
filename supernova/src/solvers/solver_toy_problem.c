#include "adaptive_rk.h"
#include "solver_toy_problem.h"
#include "solver_configurations/rk4.h"
#include <stdio.h>
#include <math.h>

void simple_ode(double t, double jd, double y[VEC_SIZE], double dydt[VEC_SIZE])
{
    dydt[0] = 2 * (pow(t, 3) + t) / y[0];

    for (size_t i = 1; i < VEC_SIZE; i++)
    {
        dydt[i] = 0;
    }
}

SolverSolution *solver_toy_problem_test()
{
    ODEFunction f = simple_ode;

    double t0 = 0;
    double t1 = 1. / 86400;

    double y0[VEC_SIZE] = {1.0, 0., 0., 0., 0., 0.};

    SolverSolution *solution = adaptive_rk_solve(rk4(), f, t0, t1, y0, 1e-6, 0.05);

    return solution;
}

int main()
{
    SolverSolution *solution = solver_toy_problem_test();

    printf("Time     Expected Actual\n");
    for (size_t i = 0; i < solution->n; i++)
    {
        printf("%f %f %f\n", solution->t[i], solution->t[i] * solution->t[i] + 1, solution->y[i][0]);
    }

    free_solver_solution(solution);
    return 0;
}
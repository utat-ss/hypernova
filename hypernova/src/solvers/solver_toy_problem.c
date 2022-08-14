#include "adaptive_rk.h"
#include "solver_toy_problem.h"
#include "solver_configurations.h"
#include <stdio.h>
#include <math.h>

void simple_ode(double t, double jd, double y[VEC_SIZE], double dydt[VEC_SIZE], Spacecraft Spacecraft)
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
    Problem problem = {
        .t0 = 0,
        .t1 = (1. / 86400),
        .y0 = {1, 0, 0, 0, 0, 0},
        .spacecraft = {.mass = 1}};

    SolverSolution *solution = adaptive_rk_solve(rk4(), f, problem, 1e-6, 0.05);

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
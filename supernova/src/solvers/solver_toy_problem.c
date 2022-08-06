#include "solver_toy_problem.h"
#include "adaptive_rk.h"
#include <stdio.h>
#include <math.h>

void simple_ode(double t, double jd, double y[VEC_SIZE], double dydt[VEC_SIZE])
{
    dydt[0] = 2 * (pow(t, 3) + t) / y[0];

    for (int i = 1; i < VEC_SIZE; i++)
    {
        dydt[i] = 0;
    }
}

void trivial_error_correlation(double h, double F[MAX_BUTCHER_TABLEAU_SIZE][VEC_SIZE], double *e)
{
    *e = 0;
}

void solver_toy_problem_test()
{
    // Create RK4 solver
    double RK4_A[MAX_BUTCHER_TABLEAU_SIZE][4] = {
        {0, 0, 0, 0},
        {0.5, 0, 0, 0},
        {0.5, 0.5, 0, 0},
        {1, 0, 0, 0}};

    double RK4_b[4] = {1.0 / 6.0, 1.0 / 3.0, 1.0 / 3.0, 1.0 / 6.0};
    double RK4_c[4] = {0.0, 1.0 / 2.0, 1.0 / 2.0, 1.0};

    ButcherTableau weights = {
        .A = RK4_A,
        .b = RK4_b,
        .c = RK4_c};

    RKSolver solver = {
        .weights = &weights,
        .num_stages = 4,
        .order = 4};

    ODEFunction f = simple_ode;

    double t0 = 0;
    double t1 = 1. / 86400;

    double y0[VEC_SIZE] = {1.0, 0., 0., 0., 0., 0.};

    SolverSolution *solution = adaptive_rk_solve(&solver, f, trivial_error_correlation, t0, t1, y0, 1e-6, 0.1);

    for (int i = 0; i < solution->n; i++)
    {
        printf("%f %f %f\n", solution->t[i], solution->jd[i], solution->y[i][0]);
    }

    free_solver_solution(solution);
}

int main() {
    solver_toy_problem_test();
    return 0;
}
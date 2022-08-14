#include "../solver_configurations.h"

double trivial_error_correlation(double h, double F[MAX_BUTCHER_TABLEAU_SIZE][VEC_SIZE])
{
    return 0.0;
}

RKSolver rk4()
{
    // derivative weights
    static const double RK4_A[MAX_BUTCHER_TABLEAU_SIZE][MAX_BUTCHER_TABLEAU_SIZE] = {
        {0, 0, 0, 0},
        {0.5, 0, 0, 0},
        {0.5, 0.5, 0, 0},
        {1, 0, 0, 0}};

    // next step weights
    static const double RK4_b[4] = {1.0 / 6.0, 1.0 / 3.0, 1.0 / 3.0, 1.0 / 6.0};

    // evaluation points
    static const double RK4_c[4] = {0.0, 1.0 / 2.0, 1.0 / 2.0, 1.0};

    static const ButcherTableau weights = {
        .A = RK4_A,
        .b = RK4_b,
        .c = RK4_c};

    static RKSolver solver = {
        .weights = weights,
        .err_corr = trivial_error_correlation,
        .is_adaptive = false,
        .num_stages = 4,
        .order = 4};

    return solver;
}

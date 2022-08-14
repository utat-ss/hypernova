#include "../solver_configurations.h"

#include <math.h>

double rk45_error_correlation(double h, double F[MAX_BUTCHER_TABLEAU_SIZE][VEC_SIZE])
{
    // F: array of slopes at each stage
    double e = 0.0;

    static const double CT[6] = {1.0 / 360.0, 0.0, -128.0 / 4275.0, -2197.0 / 75240.0, 1.0 / 50.0, 2.0 / 55.0};

    for (size_t step = 0; step < 6; step++)
    {
        for (size_t component = 0; component < 3; component++)
        // only take position component of error
        {
            e += h * CT[step] * F[step][component];
        }
    }

    return e;
}

RKSolver rk45()
{
    // derivative weights
    static const double RK45_A[MAX_BUTCHER_TABLEAU_SIZE][MAX_BUTCHER_TABLEAU_SIZE] = {
        {0, 0, 0, 0, 0},
        {0.25, 0, 0, 0, 0},
        {3.0 / 32.0, 9.0 / 32.0, 0, 0, 0},
        {1932.0 / 2197.0, -7200.0 / 2197.0, 7296.0 / 2197.0, 0, 0},
        {439.0 / 216.0, -8.0, 3680.0 / 513.0, -845.0 / 4104.0, 0},
        {-8.0 / 27.0, 2.0, -3544.0 / 2565.0, 1859.0 / 4104.0, -11.0 / 40.0}};

    // next step weights
    static const double RK45_b[6] = {16.0 / 135.0, 0.0, 6656.0 / 12825.0, 28561.0 / 56430.0, -9.0 / 50.0, 2.0 / 55.0};

    // evaluation points
    static const double RK45_c[6] = {0.0, 1.0 / 4.0, 3.0 / 8.0, 1.0 / 2.0, 1.0 / 2.0, 1.0 / 2.0};

    static const ButcherTableau weights = {
        .A = RK45_A,
        .b = RK45_b,
        .c = RK45_c};

    static RKSolver solver = {
        .weights = weights,
        .err_corr = rk45_error_correlation,
        .is_adaptive = true,
        .num_stages = 6,
        .order = 5};
    return solver;
}

#include "../solver_configurations.h"
#include <math.h>

SymplecticSolver yoshida4()
{

    const double w0 = -pow(2.0, 1.0 / 3.0) / (2 - pow(2.0, 1.0 / 3.0));
    const double w1 = 1.0 / (2 - pow(2.0, 1.0 / 3.0));

    static double yoshida4_c[4] = {w1 / 2, (w0 + w1) / 2, (w0 + w1) / 2, w1 / 2};
    static double yoshida4_d[4] = {w1, w0, w1, 0.0};

    static SymplecticSolver solver = {
        .num_stages = 4,
        .c = yoshida4_c,
        .d = yoshida4_d};
    return solver;
}
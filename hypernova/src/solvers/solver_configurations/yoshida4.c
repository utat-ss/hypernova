#include "../solver_configurations.h"
#include <math.h>

SymplecticSolver yoshida4()
{

    const double w0 = -pow(2.0, 1.0 / 3.0) / (2 - pow(2.0, 1.0 / 3.0));
    const double w1 = 1.0 / (2 - pow(2.0, 1.0 / 3.0));

    static double yoshida4_c[4] = {0, 0, 0, 0};
    yoshida4_c[0] = w1 / 2;
    yoshida4_c[1] = (w0 + w1) / 2;
    yoshida4_c[2] = (w0 + w1) / 2;
    yoshida4_c[3] = w1 / 2;

    static double yoshida4_d[4] = {0, 0, 0, 0};
    yoshida4_d[0] = w1;
    yoshida4_d[1] = w0;
    yoshida4_d[2] = w1;
    yoshida4_d[3] = 0.0;

    static SymplecticSolver solver = {
        .num_stages = 4,
        .c = yoshida4_c,
        .d = yoshida4_d};
    return solver;
}
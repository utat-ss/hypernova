#include "../solver_configurations.h"

#include <math.h>

SymplecticSolver yoshida8()
{
    const double w0 = -pow(2.0, 1.0 / 3.0) / (2 - pow(2.0, 1.0 / 3.0));
    const double w1 = -0.161582374150097E1;
    const double w2 = -0.244699182370524E1;
    const double w3 = -0.716989419708120E-2;
    const double w4 = 0.244002732616735E1;
    const double w5 = 0.157739928123617E0;
    const double w6 = 0.182020630970714E1;
    const double w7 = 0.104242620869991E1;

    static double yoshida8_c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    yoshida8_c[0] = w7 / 2;
    yoshida8_c[1] = (w6 + w7) / 2;
    yoshida8_c[2] = (w6 + w5) / 2;
    yoshida8_c[3] = (w5 + w4) / 2;
    yoshida8_c[4] = (w4 + w3) / 2;
    yoshida8_c[5] = (w3 + w2) / 2;
    yoshida8_c[6] = (w2 + w1) / 2;
    yoshida8_c[7] = (w0 + w1) / 2;
    yoshida8_c[8] = (w0 + w1) / 2;
    yoshida8_c[9] = (w2 + w1) / 2;
    yoshida8_c[10] = (w3 + w2) / 2;
    yoshida8_c[11] = (w4 + w3) / 2;
    yoshida8_c[12] = (w5 + w4) / 2;
    yoshida8_c[13] = (w6 + w5) / 2;
    yoshida8_c[14] = (w6 + w7) / 2;
    yoshida8_c[15] = w7 / 2;

    static double yoshida8_d[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    yoshida8_d[0] = w7;
    yoshida8_d[1] = w6;
    yoshida8_d[2] = w5;
    yoshida8_d[3] = w4;
    yoshida8_d[4] = w3;
    yoshida8_d[5] = w2;
    yoshida8_d[6] = w1;
    yoshida8_d[7] = w0;
    yoshida8_d[8] = w1;
    yoshida8_d[9] = w2;
    yoshida8_d[10] = w3;
    yoshida8_d[11] = w4;
    yoshida8_d[12] = w5;
    yoshida8_d[13] = w6;
    yoshida8_d[14] = w7;
    yoshida8_d[15] = 0.0;

    static SymplecticSolver solver = {
        .num_stages = 16,
        .c = yoshida8_c,
        .d = yoshida8_d};
    return solver;
}
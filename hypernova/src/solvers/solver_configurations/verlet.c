#include "../solver_configurations.h"

SymplecticSolver verlet()
{
    static double verlet_c[2] = {0.0, 1.0};
    static double verlet_d[2] = {0.5, 0.5};

    static SymplecticSolver solver = {
        .num_stages = 2,
        .c = verlet_c,
        .d = verlet_d};
    return solver;
}
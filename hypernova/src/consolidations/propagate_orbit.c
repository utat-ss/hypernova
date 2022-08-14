#include "propagate_orbit.h"
#include "../physics/earth_gravity/simplified_gravity.h"
#include "../solvers/solver_configurations.h"
#include "../solvers/adaptive_rk.h"
#include "../solvers/symplectic.h"

void physics_ode(double t, double jd, double y[VEC_SIZE], double dydt[VEC_SIZE], Spacecraft spacecraft)
{
    double f[3];
    simplified_gravity(t, y, f, spacecraft);

    // Update position derivatives
    for (size_t i = 0; i < 3; i++)
    {
        dydt[i] = y[i + 3];
    }
    // Update velocity derivatives
    for (size_t i = 3; i < 6; i++)
    {
        dydt[i] = f[i - 3] / spacecraft.mass;
    }
}

Spacecraft initialize_spacecraft(double mass)
{
    Spacecraft spacecraft;
    spacecraft.mass = mass;

    // TODO PROPER AERODYNAMICS
    spacecraft.aerodynamic_area = 0;
    spacecraft.drag_coefficient = 0;
    return spacecraft;
}

Problem initialize_problem(double t0, double t1, double y0[VEC_SIZE], Spacecraft spacecraft)
{
    Problem problem = {
        .t0 = t0,
        .t1 = t1,
        .y0 = {y0[0], y0[1], y0[2], y0[3], y0[4], y0[5]},
        .spacecraft = spacecraft};
    return problem;
}

SolverSolution *propagate_orbit(Problem problem, double timestep)
{
    ODEFunction f = physics_ode;
    // SolverSolution *solution = adaptive_rk_solve(rk45(), f, problem, 1e-3, timestep);
    SolverSolution *solution = symplectic_solve(yoshida4(), f, problem, timestep);

    return solution;
}
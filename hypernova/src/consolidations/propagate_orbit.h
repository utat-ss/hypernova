#ifndef PROPAGATE_ORBIT_H
#define PROPAGATE_ORBIT_H

#include "../abstractions/solver_abstractions.h"

Problem initialize_problem(double t0, double t1, double y0[VEC_SIZE], Spacecraft spacecraft);
Spacecraft initialize_spacecraft(double mass);
SolverSolution *propagate_orbit(Problem problem, double timestep);

#endif // PROPAGATE_ORBIT_H

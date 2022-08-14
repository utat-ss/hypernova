#ifndef SOLVER_CONFIGURATIONS_H
#define SOLVER_CONFIGURATIONS_H

#include "../../abstractions/solver_abstractions.h"

RKSolver rk4();
RKSolver rk45();
SymplecticSolver verlet();
SymplecticSolver yoshida4();

#endif // SOLVER_CONFIGURATIONS_H
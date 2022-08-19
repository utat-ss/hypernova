#ifndef SOLVER_CONFIGURATIONS_H
#define SOLVER_CONFIGURATIONS_H

#include "../../abstractions/solver_abstractions.h"

RKSolver rk4();
RKSolver rk45();
RKSolver rk1012();
SymplecticSolver verlet();
SymplecticSolver yoshida4();
SymplecticSolver yoshida8();

#endif // SOLVER_CONFIGURATIONS_H
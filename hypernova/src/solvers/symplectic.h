#ifndef SYMPLECTIC_H
#define SYMPLECTIC_H

#include "../abstractions/solver_abstractions.h"

SolverSolution *symplectic_solve(SymplecticSolver solver, ODEFunction f, Problem problem, double h);

#endif // SYMPLECTIC_H
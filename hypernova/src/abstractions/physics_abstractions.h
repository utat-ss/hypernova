#ifndef PHYSICS_ABSTRACTIONS_H
#define PHYSICS_ABSTRACTIONS_H

#include "../constants/program_constants.h"
#include "spacecraft.h"

typedef void (*ForceModel)(double t, double y[VEC_SIZE], double f[3], Spacecraft *spacecraft);

#endif
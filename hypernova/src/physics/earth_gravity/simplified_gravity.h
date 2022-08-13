#ifndef SIMPLIFIED_GRAVITY_H
#define SIMPLIFIED_GRAVITY_H

#include "../../abstractions/physics_abstractions.h"
#include "../../constants/physical_constants.h"

void simplified_gravity(double t, double y[VEC_SIZE], double f[3], Spacecraft spacecraft);

#endif // SIMPLIFIED_GRAVITY_H
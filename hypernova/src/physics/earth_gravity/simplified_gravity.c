#include "simplified_gravity.h"
#include "../../abstractions/spacecraft.h"
#include <math.h>

void simplified_gravity(double t, double y[VEC_SIZE], double f[3], Spacecraft spacecraft)
{
    double r = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);

    for (int i = 0; i < 3; i++)
    {
        f[i] = -G * MASS_EARTH * spacecraft.mass / (r * r * r) * y[i];
    }
}
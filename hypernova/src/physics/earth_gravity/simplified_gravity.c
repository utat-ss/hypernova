#include "simplified_gravity.h"
#include "../../abstractions/spacecraft.h"
#include <math.h>
#include <stdlib.h>

void simplified_gravity(double t, double y[VEC_SIZE], double f[3], Spacecraft spacecraft)
{
    double r = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);

    for (size_t i = 0; i < 3; i++)
    {
        f[i] = -MU_EARTH * spacecraft.mass / (r * r * r) * y[i];
    }
}

void perturbation_J2(double t, double y[VEC_SIZE], double f[3], Spacecraft spacecraft)
{
    double r = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);

    // prefactor for J2
    double factor = 3. / 2. * (J2_EARTH * MU_EARTH * RADIUS_EARTH_SQUARED / pow(r, 4)) * spacecraft.mass;
    double factor2 = 5 * y[2] * y[2] / (r * r);

    f[0] += factor * (y[0] / r * (factor2 - 1));
    f[1] += factor * (y[1] / r * (factor2 - 1));
    f[2] += factor * (y[2] / r * (factor2 - 3));
}

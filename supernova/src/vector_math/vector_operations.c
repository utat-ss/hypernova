#include "vector_operations.h"

void cross(double u[3], double v[3], double w[3])
{
    /*
    Performs cross product on 3-vectors.
    w = u x v
    */
    w[0] = u[1] * v[2] - v[1] * u[2];
    w[1] = u[2] * v[0] - v[2] * u[0];
    w[2] = u[0] * v[1] - v[0] * u[1];
}

double dot(double u[3], double v[3])
{
    /*
    Performs dot product on 3-vectors.
    return u (dot) v
    */
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}
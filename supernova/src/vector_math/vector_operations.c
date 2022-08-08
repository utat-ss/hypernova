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

void matrix_times_vector(double A[3][3], double x[3], double y[3])
{
    /*
    Performs matrix-vector multiplication.
    y = A x
    */
    y[0] = A[0][0] * x[0] + A[0][1] * x[1] + A[0][2] * x[2];
    y[1] = A[1][0] * x[0] + A[1][1] * x[1] + A[1][2] * x[2];
    y[2] = A[2][0] * x[0] + A[2][1] * x[1] + A[2][2] * x[2];
}

void matrix_times_matrix(double A[3][3], double B[3][3], double C[3][3])
{
    /*
    Performs matrix-matrix multiplication.
    C = A x B
    */
    C[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0];
    C[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1] + A[0][2] * B[2][1];
    C[0][2] = A[0][0] * B[0][2] + A[0][1] * B[1][2] + A[0][2] * B[2][2];
    C[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0];
    C[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1] + A[1][2] * B[2][1];
    C[1][2] = A[1][0] * B[0][2] + A[1][1] * B[1][2] + A[1][2] * B[2][2];
    C[2][0] = A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0];
    C[2][1] = A[2][0] * B[0][1] + A[2][1] * B[1][1] + A[2][2] * B[2][1];
    C[2][2] = A[2][0] * B[0][2] + A[2][1] * B[1][2] + A[2][2] * B[2][2];
}

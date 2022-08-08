#ifndef VECTOR_OPERATIONS_H
#define VECTOR_OPERATIONS_H

void cross(double u[3], double v[3], double w[3]);

double dot(double u[3], double v[3]);

void matrix_times_vector(double A[3][3], double x[3], double y[3]);

void matrix_times_matrix(double A[3][3], double B[3][3], double C[3][3]);

#endif
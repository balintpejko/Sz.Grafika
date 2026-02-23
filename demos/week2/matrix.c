#include "matrix.h"
#include <stdio.h>
#include <math.h>

#define sinf(x) (float)sin((double)(x))
#define cosf(x) (float)cos((double)(x))

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void scalar_multiply_matrix(const float a[3][3], float scalar, float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] * scalar;
        }
    }
}

void init_identity_matrix(float Ematrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            if (i == j) {
                Ematrix[i][j] = 1.0;
            } else {
                Ematrix[i][j] = 0.0;
            }
        }
    }
}

void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    init_zero_matrix(c);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transform_point(const float matrix[3][3], const float point[3], float result[3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        result[i] = 0.0;
        for (j = 0; j < 3; ++j) {
            result[i] += matrix[i][j] * point[j];
        }
    }
}

void scale(float matrix[3][3], float scalar, float result[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
}

void shift(const float input[3][3], float tx, float ty, float result[3][3]) {
    float T[3][3];
    init_identity_matrix(T);
    T[0][2] = tx; 
    T[1][2] = ty; 
    
    multiply_matrices(T, input, result);
}

void rotate(const float input[3][3], float angle, float result[3][3]) {
    float radians = angle * (M_PI / 180.0);
    float c = cosf(radians);
    float s = sinf(radians);
    
    float R[3][3] = {
        {c, -s, 0},
        {s,  c, 0},
        {0,  0, 1}
    };
    
    multiply_matrices(R, input, result);
}

void copy_matrix(const float source[3][3], float destination[3][3]) {
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            destination[i][j] = source[i][j];
        }
    }
}
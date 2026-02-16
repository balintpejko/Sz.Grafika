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
    int i;
    int j;
    int k;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = 0.0;
            for (k = 0; k < 3; ++k) {
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

void shift(float matrix[3][3], float x, float y, float result[3][3])
{
    result[0][0] = matrix[0][0];
    result[0][1] = matrix[0][1];
    result[0][2] = matrix[0][2] + x;

    result[1][0] = matrix[1][0];
    result[1][1] = matrix[1][1];
    result[1][2] = matrix[1][2] + y;

    result[2][0] = matrix[2][0];
    result[2][1] = matrix[2][1];
    result[2][2] = matrix[2][2];
}

void rotate(float matrix[3][3], float angle, float result[3][3])
{
    float radians = angle * M_PI / 180.0;
    float cos_angle = cosf(radians);
    float sin_angle = sinf(radians);

    result[0][0] = matrix[0][0] * cos_angle - matrix[0][1] * sin_angle;
    result[0][1] = matrix[0][0] * sin_angle + matrix[0][1] * cos_angle;
    result[0][2] = matrix[0][2];

    result[1][0] = matrix[1][0] * cos_angle - matrix[1][1] * sin_angle;
    result[1][1] = matrix[1][0] * sin_angle + matrix[1][1] * cos_angle;
    result[1][2] = matrix[1][2];

    result[2][0] = matrix[2][0];
    result[2][1] = matrix[2][1];
    result[2][2] = matrix[2][2];
}
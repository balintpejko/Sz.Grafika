#ifndef MATRIX_H
#define MATRIX_H

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);

/**
 * Print the elements of the matrix.
 */
void print_matrix(const float matrix[3][3]);

/**
 * Add matrices.
 */
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

void init_identity_matrix(float Ematrix[3][3]);

void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

void scalar_multiply_matrix(const float a[3][3], float scalar, float c[3][3]);

void transform_point(const float matrix[3][3], const float point[3], float result[3]);

void scale(float matrix[3][3], float scalar, float result[3][3]);

void shift(float matrix[3][3], float x, float y, float result[3][3]);

void rotate(float matrix[3][3], float angle, float result[3][3]);


#endif // MATRIX_H


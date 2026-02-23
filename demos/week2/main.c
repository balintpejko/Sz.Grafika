#include "matrix.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    float T1[3][3], T2[3][3], R[3][3];
    float tmp[3][3], M[3][3];

    init_identity_matrix(T1);
    shift(T1, 0.0f, 3.0f, tmp);
    copy_matrix(tmp, T1);
    
    init_identity_matrix(R);
    R[1][1] = -1.0f;

    init_identity_matrix(T2);
    shift(T2, 0.0f, -3.0f, tmp);
    copy_matrix(tmp, T2);

    multiply_matrices(R, T1, tmp);
    multiply_matrices(T2, tmp, M);   
    print_matrix(M);
    
	return 0;
}


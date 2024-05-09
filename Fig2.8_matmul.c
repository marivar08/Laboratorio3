#include <stdio.h>

void mm_ijk_par(int N, int M, int P, double* A, double* B, double* C)
{
    int i, j, k;

#pragma omp parallel 
#pragma omp for collapse(2) private(k) schedule(static,10)  
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            for (k = 0; k < P; k++)
                *(C + (i * M + j)) += *(A + (i * P + k)) * *(B + (k * M + j));
}

int main() {

    // Definir las matrices de prueba A y B
    double A[4][4] = { {1, 2,3,4}, {3, 4,5,6}, {5, 6,7,8}, {7, 8,9,10} };
    double B[4][4] = { {1, 2,3,4}, {3, 4,5,6}, {5, 6,7,8}, {7, 8,9,10} };

    // Matriz para almacenar el resultado de la multiplicación
    double C[2][2] = { {0, 0}, {0, 0} };

    // Llamar a la función mm_ijk_par para calcular C = A * B
    mm_ijk_par(2, 2, 2, (double*)A, (double*)B, (double*)C);

    int N = 2;  
    int M = 2;  
    int P = 2;

    // Imprimir la matriz resultante
    printf("Matriz resultante C = A * B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%lf ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

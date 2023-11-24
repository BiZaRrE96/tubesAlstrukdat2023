#include "matrix.h"

int main()
{
    Matrix m1;
    readMatrix(&m1, 2, 2);
    printf("\n");
    Matrix m2;
    readMatrix(&m2, 2, 2);
    printf("\n");
    if (isMatrixEqual(m1, m2))
    {
        printf("Matrix sama\n");
    }
    else
    {
        printf("Matrix beda\n");
    }
    printf("\n");
    printf ("Matriks M1: \n ");
    displayMatrix(m1);
    printf("\n");
    printf ("Matriks M2: \n ");
    displayMatrix(m2);
    printf("\n");
}
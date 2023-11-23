// NAMA PEMBUAT : Christian Justin Hendrawan
// NIM : 13522135
// TOPIK : ADT MATRIX

/* ********** Definisi TYPE Matrix dengan Index dan elemen integer ********** */

#ifndef MATRIX_H
#define MATRIX_H

#include "../boolean/boolean.h"
#include <stdio.h>

/* Ukuran maksimum baris dan kolom */
#define ROW_CAP_MATRIX 100
#define COL_CAP_MATRIX 100

typedef int IdxType_MATRIX_INT; /* Index baris, kolom */
typedef int ElType_MATRIX_INT;
typedef struct
{
    ElType_MATRIX_INT mem[ROW_CAP_MATRIX][COL_CAP_MATRIX];
    int rowEff; /* banyaknya/ukuran baris yg terdefinisi */
    int colEff; /* banyaknya/ukuran kolom yg terdefinisi */
} Matrix;
/* rowEff >= 1 dan colEff >= 1 */
/* Indeks matriks yang digunakan: [0..ROW_CAP_MATRIX-1][0..COL_CAP_MATRIX-1] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* *** Selektor *** */
#define ROW_EFF(M) (M).rowEff
#define COL_EFF(M) (M).colEff
#define ELMT_MATRIX(M, i, j) (M).mem[(i)][(j)]

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void createMatrix(int nRows, int nCols, Matrix *m)
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
{
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;

    for (IdxType_MATRIX_INT i = 0; i < nRows; i++)
    {
        for (IdxType_MATRIX_INT j = 0; j < nCols; j++)
        {
            ELMT_MATRIX(*m, i, j) = 0;
        }
    }
}

/* *** Selektor "Dunia Matrix" *** */
boolean isMatrixIdxValid(int i, int j)
/* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */
{
    return ((i >= 0 && i < ROW_CAP_MATRIX) && (j >= 0 && j < COL_CAP_MATRIX));
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
IdxType_MATRIX_INT getLastIdxRow(Matrix m)
{
    return ROW_EFF(m) - 1;
}

/* Mengirimkan Index baris terbesar m */
IdxType_MATRIX_INT getLastIdxCol(Matrix m)
{
    return COL_EFF(m) - 1;
}

/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mOut)
/* Melakukan assignment mOut <- mIn */
{
    createMatrix(ROW_EFF(mIn), COL_EFF(mIn), mOut);

    for (IdxType_MATRIX_INT i = 0; i < ROW_EFF(mIn); i++)
        for (IdxType_MATRIX_INT j = 0; j < COL_EFF(mIn); j++)
            ELMT_MATRIX(*mOut, i, j) = ELMT_MATRIX(mIn, i, j);

    for (IdxType_MATRIX_INT i = 0; i < ROW_EFF(mIn); i++)
        for (IdxType_MATRIX_INT j = 0; j < COL_EFF(mIn); j++)
            ELMT_MATRIX(*mOut, i, j) = ELMT_MATRIX(mIn, i, j);
}

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol)
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
{
    createMatrix(nRow, nCol, m);
    int i, j;
    for (i = 0; i < nRow; i++)
    {
        for (j = 0; j < nCol; j++)
        {
            scanf("%d", &ELMT_MATRIX(*m, i, j));
        }
    }
}

void displayMatrix(Matrix m)
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
    for (IdxType_MATRIX_INT i = 0; i < ROW_EFF(m); i++)
    {
        for (IdxType_MATRIX_INT j = 0; j < COL_EFF(m); j++)
        {
            printf("%d", ELMT_MATRIX(m, i, j));
            if (j < getLastIdxCol(m))
                printf(" ");
        }
        printf("\n");
    }
}

boolean isMatrixSizeEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
/* yaitu RowEff(m1) = RowEff (m2) dan ColEff (m1) = ColEff (m2) */
{
    return ROW_EFF(m1) == ROW_EFF(m2) && COL_EFF(m1) == COL_EFF(m2);
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
boolean isMatrixEqual(Matrix m1, Matrix m2)
{
    if (isMatrixSizeEqual(m1, m2))
    {
        for (IdxType_MATRIX_INT i = 0; i < ROW_EFF(m1); i++)
        {
            for (IdxType_MATRIX_INT j = 0; j < COL_EFF(m1); j++)
            {
                if (ELMT_MATRIX(m1, i, j) != ELMT_MATRIX(m2, i, j))
                    return false;
            }
        }
        return true;
    }
    return false;
}

#endif
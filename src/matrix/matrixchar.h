/* ********** Definisi TYPE Matrixchar dengan Index dan elemen integer ********** */

#ifndef Matrixchar_H
#define Matrixchar_H

#include "../boolean/boolean.h"
#include <stdio.h>

/* Ukuran maksimum baris dan kolom */
#define ROW_CAP 100
#define COL_CAP 100

typedef int IdxType; /* Index baris, kolom */
typedef char MElType;
typedef struct
{
    MElType mem[ROW_CAP][COL_CAP];
    int rowEff; /* banyaknya/ukuran baris yg terdefinisi */
    int colEff; /* banyaknya/ukuran kolom yg terdefinisi */
} Matrixchar;
/* rowEff >= 1 dan colEff >= 1 */
/* Indeks matriks yang digunakan: [0..ROW_CAP-1][0..COL_CAP-1] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* *** Selektor *** */
#define ROW_EFF(M) (M).rowEff
#define COL_EFF(M) (M).colEff
#define MELMT(M, i, j) (M).mem[(i)][(j)]

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrixchar *** */
void createMatrixchar(int nRows, int nCols, Matrixchar *m)
/* Membentuk sebuah Matrixchar "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
{
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;

    for (IdxType i = 0; i < nRows; i++)
    {
        for (IdxType j = 0; j < nCols; j++)
        {
            MELMT(*m, i, j) = 0;
        }
    }
}

/* *** Selektor "Dunia Matrixchar" *** */
boolean isMatrixcharIdxValid(int i, int j)
/* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */
{
    return ((i >= 0 && i < ROW_CAP) && (j >= 0 && j < COL_CAP));
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
IdxType getLastIdxRow(Matrixchar m)
{
    return ROW_EFF(m) - 1;
}

/* Mengirimkan Index baris terbesar m */
IdxType getLastIdxCol(Matrixchar m)
{
    return COL_EFF(m) - 1;
}

/* Mengirimkan Index kolom terbesar m */
boolean isIndexEff(Matrixchar m, IdxType i, IdxType j)
/* Mengirimkan true jika i, j adalah Index efektif bagi m */ {
    return (i >= 0 && i <= getLastIdxRow(m) && j >= 0 && j <= getLastIdxCol(m));
}

MElType getMELMTDiagonal(Matrixchar m, IdxType i)
/* Mengirimkan elemen m(i,i) */
{
    return MELMT(m, i, i);
}

/* ********** Assignment  Matrixchar ********** */
void copyMatrixchar(Matrixchar mIn, Matrixchar *mOut)
/* Melakukan assignment mOut <- mIn */
{
    createMatrixchar(ROW_EFF(mIn), COL_EFF(mIn), mOut);

    for (IdxType i = 0; i < ROW_EFF(mIn); i++)
        for (IdxType j = 0; j < COL_EFF(mIn); j++)
            MELMT(*mOut, i, j) = MELMT(mIn, i, j);

    for (IdxType i = 0; i < ROW_EFF(mIn); i++)
        for (IdxType j = 0; j < COL_EFF(mIn); j++)
            MELMT(*mOut, i, j) = MELMT(mIn, i, j);
}

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrixchar(Matrixchar *m, int nRow, int nCol)
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrixchar(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
{
    createMatrixchar(nRow, nCol, m);
    int i, j;
    for (i = 0; i < nRow; i++)
    {
        for (j = 0; j < nCol; j++)
        {
            scanf("%d", &MELMT(*m, i, j));
        }
    }
}

void displayMatrixchar(Matrixchar m)
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
    for (IdxType i = 0; i < ROW_EFF(m); i++)
    {
        for (IdxType j = 0; j < COL_EFF(m); j++)
        {
            printf("%d", MELMT(m, i, j));
            if (j < getLastIdxCol(m))
                printf(" ");
        }
        printf("\n");
    }
}

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
Matrixchar addMatrixchar(Matrixchar m1, Matrixchar m2)
{

    for (IdxType i = 0; i < ROW_EFF(m1); i++)
    {
        for (IdxType j = 0; j < COL_EFF(m1); j++)
        {
            MELMT(m1, i, j) += MELMT(m2, i, j);
        }
    }
    return m1;
}

/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil penjumlahan matriks: m1 + m2 */
Matrixchar subtractMatrixchar(Matrixchar m1, Matrixchar m2)
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
{
    for (IdxType i = 0; i < ROW_EFF(m1); i++)
    {
        for (IdxType j = 0; j < COL_EFF(m1); j++)
        {
            MELMT(m1, i, j) -= MELMT(m2, i, j);
        }
    }
    return m1;
}

Matrixchar multiplyMatrixchar(Matrixchar m1, Matrixchar m2)
/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
/* Mengirim hasil perkalian matriks: salinan m1 * m2 */
{
    Matrixchar m3;
    createMatrixchar(ROW_EFF(m1), COL_EFF(m2), &m3);

    for (IdxType i = 0; i < ROW_EFF(m1); i++)
    {
        for (IdxType j = 0; j < COL_EFF(m2); j++)
        {
            for (IdxType k = 0; k < COL_EFF(m1); k++)
            {
                MELMT(m3, i, j) += MELMT(m1, i, k) * MELMT(m2, k, j);
            }
        }
    }
    return m3;
}

Matrixchar multiplyMatrixcharWithMod(Matrixchar m1, Matrixchar m2, int mod)
/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
/* Mengirim hasil perkalian matriks: salinan (m1 * m2)%mod, artinya setiap elemen Matrixchar hasil perkalian m1 * m2 dilakukan modulo terhadap mod */
{
    Matrixchar m3;
    createMatrixchar(ROW_EFF(m1), COL_EFF(m2), &m3);

    for (IdxType i = 0; i < ROW_EFF(m1); i++)
    {
        for (IdxType j = 0; j < COL_EFF(m2); j++)
        {
            for (IdxType k = 0; k < COL_EFF(m1); k++)
            {
                MELMT(m3, i, j) += MELMT(m1, i, k) * MELMT(m2, k, j);
            }
            MELMT(m3, i, j) %= mod;
        }
    }
    return m3;
}

Matrixchar multiplyByConst(Matrixchar m, MElType x)
/* Mengirim hasil perkalian setiap elemen m dengan x */
{
    for (IdxType i = 0; i < ROW_EFF(m); i++)
    {
        for (IdxType j = 0; j < COL_EFF(m); j++)
        {
            MELMT(m, i, j) *= x;
        }
    }
    return m;
}

void pMultiplyByConst(Matrixchar *m, MElType k)
/* I.S. m terdefinisi, k terdefinisi */
/* F.S. Mengalikan setiap elemen m dengan k */
{
    for (IdxType i = 0; i < ROW_EFF(*m); i++)
    {
        for (IdxType j = 0; j < COL_EFF(*m); j++)
        {
            MELMT(*m, i, j) *= k;
        }
    }
}

boolean isMatrixcharSizeEqual(Matrixchar m1, Matrixchar m2)
/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
/* yaitu RowEff(m1) = RowEff (m2) dan ColEff (m1) = ColEff (m2) */
{
    return (ROW_EFF(m1) == ROW_EFF(m2) && COL_EFF(m1) == COL_EFF(m2));
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrixchar ********** */
boolean isMatrixcharEqual(Matrixchar m1, Matrixchar m2)
{
    if (isMatrixcharSizeEqual(m1, m2))
    {
        for (IdxType i = 0; i < ROW_EFF(m1); i++)
        {
            for (IdxType j = 0; j < COL_EFF(m1); j++)
            {
                if (MELMT(m1, i, j) != MELMT(m2, i, j))
                    return false;
            }
        }
        return true;
    }
    return false;
}

/* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
/* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
/* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
boolean isMatrixcharNotEqual(Matrixchar m1, Matrixchar m2)
/* Mengirimkan true jika m1 tidak sama dengan m2 */
{
    return !isMatrixcharEqual(m1, m2);
}

/* ********** Operasi lain ********** */
int countMELMT(Matrixchar m)
/* Mengirimkan banyaknya elemen m */
{
    return ROW_EFF(m) * COL_EFF(m);
}

/* ********** KELOMPOK TEST TERHADAP Matrixchar ********** */
boolean isSquare(Matrixchar m)
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
{
    return (ROW_EFF(m) == COL_EFF(m));
}

boolean isSymmetric(Matrixchar m)
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m)
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
{
    if (isSquare(m))
    {
        for (IdxType i = 0; i < ROW_EFF(m); i++)
        {
            for (IdxType j = 0; j < COL_EFF(m); j++)
            {
                if (MELMT(m, i, j) != MELMT(m, j, i))
                    return false;
            }
        }
        return true;
    }
    return false;
}

boolean isIdentity(Matrixchar m)
/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
{
    if (isSquare(m))
    {
        for (IdxType i = 0; i < ROW_EFF(m); i++)
        {
            for (IdxType j = 0; j < COL_EFF(m); j++)
            {
                if (i == j)
                {
                    if (MELMT(m, i, j) != 1)
                        return false;
                }
                else
                {
                    if (MELMT(m, i, j) != 0)
                        return false;
                }
            }
        }
        return true;
    }
    return false;
}

boolean isSparse(Matrixchar m)
/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi:
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
{
    int count = 0;
    for (IdxType i = 0; i < ROW_EFF(m); i++)
    {
        for (IdxType j = 0; j < COL_EFF(m); j++)
        {
            if (MELMT(m, i, j) != 0)
                count++;
        }
    }
    return (count <= 5 / 100 * countMELMT(m));
}

Matrixchar negation(Matrixchar m)
/* Menghasilkan salinan m dengan setiap elemen dinegasikan (dikalikan -1) */
{
    return multiplyByConst(m, -1);
}

void pNegation(Matrixchar *m)
/* I.S. m terdefinisi */
/* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
{
    pMultiplyByConst(m, -1);
}

float determinant(Matrixchar m)
/* Prekondisi: isSquare(m) */
/* Menghitung nilai determinan m */
{
    if (!isSquare(m))
        return 0;

    int temp_row[11];
    IdxType idx;
    int det = 1;
    int co = 1;

    for (IdxType i = 0; i < ROW_EFF(m); i++)
    {
        idx = i;
        while (MELMT(m, idx, i) == 0 && idx < ROW_EFF(m))
            idx++;

        if (idx == ROW_EFF(m))
            return 0;

        if (i != idx)
        {
            for (IdxType j = 0; j < ROW_EFF(m); j++)
            {
                MElType temp = MELMT(m, i, j);
                MELMT(m, i, j) = MELMT(m, idx, j);
                MELMT(m, idx, j) = temp;
            }
            det *= -1;
        }

        for (IdxType j = 0; j < ROW_EFF(m); j++)
        {
            temp_row[j] = MELMT(m, i, j);
        }

        for (IdxType j = i + 1; j < ROW_EFF(m); j++)
        {
            MElType temp1 = temp_row[i];
            MElType temp2 = MELMT(m, j, i);

            for (IdxType k = 0; k < ROW_EFF(m); k++)
            {
                MELMT(m, j, k) = ((temp1 * MELMT(m, j, k)) - (temp2 * temp_row[k]));
            }

            co *= temp1;
        }
    }

    for (IdxType i = 0; i < ROW_EFF(m); i++)
        det *= MELMT(m, i, i);

    return det / co;
}

Matrixchar transpose(Matrixchar m)
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. menghasilkan salinan transpose dari m, yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
{
    Matrixchar m2;
    createMatrixchar(ROW_EFF(m), COL_EFF(m), &m2);

    for (IdxType i = 0; i < ROW_EFF(m); i++)
    {
        for (IdxType j = 0; j < COL_EFF(m); j++)
        {
            MELMT(m2, i, j) = MELMT(m, j, i);
        }
    }
    return m2;
}

void pTranspose(Matrixchar *m)
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
{
    *m = transpose(*m);
}

#endif
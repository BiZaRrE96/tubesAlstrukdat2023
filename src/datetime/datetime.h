#ifndef DATETIME_H
#define DATETIME_H

#include "../Boolean/boolean.h"
#include "../Time/time.h"
// #include <stdio.h>

/* *** Definisi TYPE DATETIME <DD/MM/YY HH:MM:SS> *** */
typedef struct
{
    int DD;   /* integer [1..31] */
    int MM;   /* integer [1..12] */
    int YYYY; /* integer [1900..2030] */
    TIME T;
} DATETIME;

/* *** Notasi Akses: selektor DATETIME *** */
#define Day(D) (D).DD
#define Month(D) (D).MM
#define Year(D) (D).YYYY
#define Time(D) (D).T

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
int GetMaxDay(int M, int Y)
/* Mengirimkan jumlah hari maksimum pada bulan M dan tahun Y */
/* Prekondisi: 1 <= M <= 12*/
/* Hint: Perhatikan Leap Year. Leap Year adalah tahun dengan 29 hari pada bulan Februari */
/* Aturan Leap Year: */
/* 1. Jika angka tahun itu habis dibagi 400, maka tahun itu sudah pasti tahun kabisat. 8*/
/* 2. Jika angka tahun itu tidak habis dibagi 400 tetapi habis dibagi 100, maka tahun itu sudah pasti bukan merupakan tahun kabisat. */
/* 3. Jika angka tahun itu tidak habis dibagi 400, tidak habis dibagi 100 akan tetapi habis dibagi 4, maka tahun itu merupakan tahun kabisat. */
/* 4. Jika angka tahun tidak habis dibagi 400, tidak habis dibagi 100, dan tidak habis dibagi 4, maka tahun tersebut bukan merupakan tahun kabisat. */
{
    if (M == 2) {
        if (Y % 400 == 0) {
            return 29;
        } else if (Y % 100 == 0) {
            return 28;
        } else if (Y % 4 == 0) {
            return 29;
        } else {
            return 28;
        }
    } else if (M == 4 || M == 6 || M == 9 || M == 11) {
        return 30;
    } else {
        return 31;
    }
}

boolean IsDATETIMEValid(int D, int M, int Y, int h, int m, int s)
/* Mengirim true jika D,M,Y,h,m,s dapat membentuk D yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah DATETIME */
{
    boolean monthValid = (M >= 1 && M <= 12);
    boolean dayValid = (D >= 1 && D <= GetMaxDay(M, Y));
    boolean timeValid = IsTIMEValid(h, m, s);
    return monthValid && dayValid && timeValid;
}

/* *** Konstruktor: Membentuk sebuah DATETIME dari komponen-komponennya *** */
void CreateDATETIME(DATETIME *D, int DD, int MM, int YYYY, int hh, int mm, int ss)
/* Membentuk sebuah DATETIME dari komponen-komponennya yang valid */
/* Prekondisi : DD, MM, YYYY, h, m, s valid untuk membentuk DATETIME */
{
    Day(*D) = DD;
    Month(*D) = MM;
    Year(*D) = YYYY;
    Hour(Time(*D)) = hh;
    Minute(Time(*D)) = mm;
    Second(Time(*D)) = ss;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaDATETIME(DATETIME *D)
/* I.S. : D tidak terdefinisi */
/* F.S. : D terdefinisi dan merupakan DATETIME yang valid */
/* Proses : mengulangi membaca komponen DD, MM, YY, h, m, s sehingga membentuk D */
/* yang valid. Tidak mungkin menghasilkan D yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen DD, MM, YY, h, m, s
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika DATETIME tidak valid maka diberikan pesan: "DATETIME tidak valid", dan pembacaan
    diulangi hingga didapatkan DATETIME yang valid. */
/* Contoh:
    32 13 2023 12 34 56
    DATETIME tidak valid
    31 12 2023 12 34 56
    --> akan terbentuk DATETIME <31,12,2023,12,34,56> */
{
    int DD, MM, YYYY, hh, mm, ss;
    scanf("%d %d %d %d %d %d", &DD, &MM, &YYYY, &hh, &mm, &ss);
    while (!IsDATETIMEValid(DD, MM, YYYY, hh, mm, ss)) {
        printf("DATETIME tidak valid\n");
        scanf("%d %d %d %d %d %d", &DD, &MM, &YYYY, &hh, &mm, &ss);
    }
    CreateDATETIME(D, DD, MM, YYYY, hh, mm, ss);
}

void TulisDATETIME(DATETIME D)
/* I.S. : D sembarang */
/* F.S. : Nilai D ditulis dg format DD/MM/YYYY HH:MM:SS */
/* Proses : menulis nilai setiap komponen D ke layar dalam format DD/MM/YYYY HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
{
    printf("%02d/%02d/%04d %02d:%02d:%02d", Day(D), Month(D), Year(D), Hour(Time(D)), Minute(Time(D)), Second(Time(D)));
}


/* *** Kelompok operasi relasional terhadap DATETIME *** */
boolean DEQ(DATETIME D1, DATETIME D2)
/* Mengirimkan true jika D1=D2, false jika tidak */
{
    return ((Day(D1) == Day(D2)) && (Month(D1) == Month(D2)) && (Year(D1) == Year(D2)) && (Hour(Time(D1)) == Hour(Time(D2))) && (Minute(Time(D1)) == Minute(Time(D2))) && (Second(Time(D1)) == Second(Time(D2))));
}

boolean DNEQ(DATETIME D1, DATETIME D2)
/* Mengirimkan true jika D1 tidak sama dengan D2 */
{
    return !DEQ(D1, D2);
}

boolean DLT(DATETIME D1, DATETIME D2)
/* Mengirimkan true jika D1<D2, false jika tidak */
{
    if (Year(D1) < Year(D2)) {
        return true;
    } else if (Year(D1) > Year(D2)) {
        return false;
    } else {
        if (Month(D1) < Month(D2)) {
            return true;
        } else if (Month(D1) > Month(D2)) {
            return false;
        } else {
            if (Day(D1) < Day(D2)) {
                return true;
            } else if (Day(D1) > Day(D2)) {
                return false;
            } else {
                return TLT(Time(D1), Time(D2));
            }
        }
    }
}

boolean DGT(DATETIME D1, DATETIME D2)
/* Mengirimkan true jika D1>D2, false jika tidak */
{
    return ((!DEQ(D1, D2)) && (!DLT(D1, D2)));
}

DATETIME DATETIMENextNDetik(DATETIME D, int N)
/* Mengirim salinan D dengan detik ditambah N */
{
    int timeInt = TIMEToDetik(Time(D)) + N;
    Time(D) = DetikToTIME(timeInt % 86400);
    Day(D) += (timeInt / 86400);
    while (Day(D) > GetMaxDay(Month(D), Year(D))) {
        Day(D) -= GetMaxDay(Month(D), Year(D));
        Month(D)++;
        if (Month(D) > 12) {
            Month(D) = 1;
            Year(D)++;
        }
    }
    
    return D;
}


DATETIME DATETIMEPrevNDetik(DATETIME D, int N)
/* Mengirim salinan D dengan detik dikurang N */
{
    int timeInt = TIMEToDetik(Time(D)) - N;
    Time(D) = DetikToTIME(86400 + (timeInt % 86400));
    // printf("{%d}\n", 86400 + timeInt % 86400);
    while (timeInt < 0) {
        Day(D)--;
        if (Day(D) < 1) {
            Month(D)--;
            if (Month(D) < 1) {
                Month(D) = 12;
                Year(D)--;
            }
            Day(D) += GetMaxDay(Month(D), Year(D));
        }
        timeInt += 86400;
    }

    return D;
    
}

/* *** Kelompok Operator Aritmetika terhadap DATETIME *** */
long int DATETIMEDurasi(DATETIME DAw, DATETIME DAkh)
/* Mengirim DAkh-DAw dlm Detik, dengan kalkulasi */
/* Prekondisi: DAkh > DAw */
{
    long int durasi = 0;
    while (Day(DAw) != Day(DAkh) || Month(DAw) != Month(DAkh) || Year(DAw) != Year(DAkh)) {
        durasi += 86400;
        Day(DAw)++;
        if (Day(DAw) > GetMaxDay(Month(DAw), Year(DAw))) {
            Day(DAw) = 1;
            Month(DAw)++;
            if (Month(DAw) > 12) {
                Month(DAw) = 1;
                Year(DAw)++;
            }
        }
    }
    durasi += TIMEToDetik(Time(DAkh)) - TIMEToDetik(Time(DAw));
    return durasi;
}

#endif
/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: ADT */
/* Deskripsi: ADT MATRIKS dan operasi-operasinya */
/* File: konvolusi.c */
/* Tanggal: 19 September 2019 */

/* *** ADT YANG DIPAKAI *** */
#include <stdio.h>
#include "matriks.h"

int main () {
/* ** Deklarasi variabel ** */
    MATRIKS A, B, C;
	int N, M, K, si, sj;
    ElType El;
	/* ** Interaksi ** */
	scanf("%d %d", &N, &M);
    BacaMATRIKS(&A, N, M);
    scanf("%d", &K);
    BacaMATRIKS(&B, K, K);
    MakeMATRIKS(N, M, &C);
    //
    for (indeks i = GetFirstIdxBrs(C); i <= GetLastIdxBrs(C); i++) {
        for (indeks j = GetFirstIdxKol(C); j <= GetLastIdxKol(C); j++) {
            si = NBrsEff(B)/2 - i + 1; /* nilai sub untuk indeks baris matriks A */
            sj = NKolEff(B)/2 - j + 1; /* nilai sub untuk indeks kolom matriks A */
            El = 0;
            /* jelajah matriks B */
            for (indeks iB = GetFirstIdxBrs(B); iB <= GetLastIdxBrs(B); iB++) {
                for (indeks jB = GetFirstIdxKol(B); jB <= GetLastIdxKol(B); jB++) {
                    if (isIdxEff(A, iB-si, jB-sj)) {
                        El += Elmt(B, iB, jB) * Elmt(A, iB-si, jB-sj);
                    }
                }
            }
            Elmt(C, i, j) = El;
        }
    }
    //
    TulisMATRIKS(C);
}

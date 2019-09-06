/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: ADT */
/* Deskripsi: ADT ARRAY dan operasi-operasinya */
/* File: marray.c */
/* Tanggal: 5 September 2019 */

/* *** ADT YANG DIPAKAI *** */
#include <stdio.h>
#include "array.h"

/* *** FUNGSI DAN PROSEDUR *** */
int nX (TabInt T, ElType X) {
/* Menghitung berapa kali X muncul pada T dan mengembalikan hasilnya */
	int count = 0;
    for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++) {
        if (Elmt(T, i) == X) {
            count++;
        }
    }
    return count;
}

int main () {
	/* ** Deklarasi variabel ** */
	TabInt T;
	ElType X;
	/* ** Interaksi ** */
	BacaIsi(&T); /* Masukan dari pengguna */
	TulisIsiTab(T); /* Menampilkan isi Tab */
	printf("\n");
	/* ** Statistik ** */
	scanf("%d", &X); /* Masukan X dari pengguna */
	printf("%d\n", nX(T, X)); /* Menampilkan banyaknya kemunculan X pada T */
	/* Pencarian X pada T */
	if (SearchB(T, X)) {
		printf("%d\n", Search1(T, X)); /* Menampilkan indeks terkecil X muncul */
	} else {
		printf("%d tidak ada\n", X); /* Menampilkan pesan X tidak ditemukan */
	}
	/* Informasi maksimum, minimum, median */
	if (X == ValMax(T)) {
		printf("maksimum\n");
	}
	if (X == ValMin(T)) {
		printf("minimum\n");
	}
	InsSortAsc(&T);
	if (X == Elmt(T, (GetLastIdx(T)-GetFirstIdx(T)+2)/2)) {
		printf("median\n");
	}
	return 0;
}

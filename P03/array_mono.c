/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: ADT */
/* Deskripsi: ADT ARRAY dan operasi-operasinya */
/* File: array_mono.c */
/* Tanggal: 5 September 2019 */

/* *** ADT YANG DIPAKAI *** */
#include <stdio.h>
#include "array.h"

/* *** FUNGSI DAN PROSEDUR *** */

int main () {
	/* ** Deklarasi variabel ** */
	TabInt T, Tasc, Tdes;
	ElType X;
	/* ** Interaksi ** */
	BacaIsi(&T); /* Masukan dari pengguna */
	/* ** Memeriksa kemonotonikan ** */
	CopyTab(T, &Tasc); /* Membuat salinan T yang akan diurutkan menaik */
	InsSortAsc(&Tasc);
	CopyTab(T, &Tdes); /* Membuat salinan T yang akan diurutkan menaik */
	MaxSortDesc(&Tdes);
	if (Elmt(Tasc, GetFirstIdx(Tasc)) == Elmt(Tdes, GetFirstIdx(Tdes))) {
		printf("Array monotonik statik\n");
	} else if (IsEQ(T, Tasc)) {
		printf("Array monotonik tidak mengecil\n");
	} else if (IsEQ(T, Tdes)) {
		printf("Array monotonik tidak membesar\n");
	} else {
		printf("Array tidak monotonik\n");
	}
	return 0;
}

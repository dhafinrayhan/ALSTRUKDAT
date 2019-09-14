/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: ADT */
/* Deskripsi: ADT ARRAY DINAMIK dan operasi-operasinya */
/* File: marraydin.c */
/* Tanggal: 12 September 2019 */

/* *** ADT YANG DIPAKAI *** */
#include <stdio.h>
#include "arraydin.h"

/* *** FUNGSI DAN PROSEDUR *** */

void berhasil (TabInt T) {
/* menampilkan MaxEl(T) dan isi array ketika operasi berhasil */
	printf("%d ", MaxElement(T));
	TulisIsiTab(T);
	printf("\n");
}

int main () {
	/* ** Deklarasi variabel ** */
	TabInt T;
	int Q, op, mxEl;
	ElType num;
	/* ** Interaksi ** */
	/* Masukan-masukan dari pengguna */
	scanf("%d", &mxEl);
	MaxEl(T) = mxEl;
	BacaIsi(&T);
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d", &num);
			if (IsFull(T)) {
				printf("array sudah penuh\n");
			} else {
				AddAsLastEl(&T, num);
				berhasil(T);
			}
		} else if (op == 2) {
			scanf("%d", &num);
			GrowTab(&T, num);
			berhasil(T);
		} else if (op == 3) {
			scanf("%d", &num);
			if (MaxElement(T) < num) {
				printf("array terlalu kecil\n");
			} else {
				ShrinkTab(&T, num);
				berhasil(T);
			}
		} else { /* op == 4 */
			CompactTab(&T);
			berhasil(T);
		}
	}
	//
	return 0;
}


/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: ADT */
/* Deskripsi: Driver ADT JAM */
/* File: mjam.c */
/* Tanggal: 29 Agustus 2019 */

#include <stdio.h>
#include "jam.h"

int main() {
	int rec;
	JAM PalingAwal = MakeJAM(23,59,59);
	JAM PalingAkhir = MakeJAM(0,0,0);
	scanf("%d", &rec);
	for (int i = 1; i <= rec; i++) {
		printf("[%d]\n", i);
		JAM J1, J2;
		long durasi;
		BacaJAM(&J1);
		BacaJAM(&J2);
		if (JLT(J1, J2)) {
			durasi = Durasi(J1, J2);
			if (JLT(J1, PalingAwal)) {
				PalingAwal = J1;
			}
			if (JGT(J2, PalingAkhir)) {
				PalingAkhir = J2;
			}
		} else {
			durasi = Durasi(J2, J1);
			if (JLT(J2, PalingAwal)) {
				PalingAwal = J2;
			}
			if (JGT(J1, PalingAkhir)) {
				PalingAkhir = J1;
			}
		}
		printf("%ld\n", durasi);
	}
	TulisJAM(PalingAwal);
	printf("\n");
	TulisJAM(PalingAkhir);
	printf("\n");
}

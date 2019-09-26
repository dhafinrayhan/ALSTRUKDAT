/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: Mesin */
/* Deskripsi: Implementasi Mesin Kata untuk menghitung kemunculan pattern */
/* File: kemunculankata.c */
/* Tanggal: 26 September 2019 */

#include <stdio.h>
#include "mesinkata.h"

int main() {
	STARTKATA();
	Kata pat = CKata;
	
	int muncul = -1;
	boolean diff;
	int j;
	do {
		for (int i = 1; i <= CKata.Length-pat.Length+1; i++) {
			diff = false;
			j = i;
			while ((!diff) && (j <= i+pat.Length-1)) {
				if (CKata.TabKata[j] != pat.TabKata[j-i+1]) {
					diff = true;
				} else {
					j++;
				}
			}
			if (j == i+pat.Length) {
				muncul++;
			}
		}
		ADVKATA();
	} while (!EndKata);
	//
	printf("%d\n", muncul);
	return 0;
}

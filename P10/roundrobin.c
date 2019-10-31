/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: ADT List Sirkuler */
/* Deskripsi: ADT List Sirkuler untuk menyelesaikan persoalan round robin */
/* File: roundrobin.c */
/* Tanggal: 31 Oktober 2019 */

#include <stdio.h>
#include "listsirkuler.h"

void DeleteRR (List *L, infotype TQ) {
/* Jika L tidak kosong, "menghapus" elemen terakhir list L, misal last, sesuai aturan round robin, yaitu:
   - jika Info(last)>TQ, maka last "diantrikan" kembali sebagai first elemen dengan Info(last)=Info(last)-TQ
   - jika Info(last)<=TQ, maka DeleteLast(L,X) dan menampilkan X ke layar */
/* Jika L kosong, cetak "List kosong" */
/* I.S. TQ terdefinisi sebagai nilai time slice pemrosesan.
   L terdefinisi, mungkin kosong. */
/* F.S. Elemen terakhir L diproses sesuai aturan round-robin.
   L mungkin menjadi kosong. */
    if (IsEmpty(*L)) {
		printf("List kosong\n");
	} else {
		address PL = First(*L);
		while (Next(PL) != First(*L)) {
			PL = Next(PL);
		}
		//
		if (Info(PL) > TQ) {
			Info(PL) -= TQ;
			First(*L) = PL;
			printf("%d\n", TQ);
		} else {
			infotype X;
			DelVLast(L, &X);
			printf("%d\n", X);
		}
	}
}

float Average (List L) {
/* Menghasilkan nilai rata-rata elemen L. L tidak kosong. */
	address P = First(L);
	float avg = Info(P);
	int c = 1;
	while (Next(P) != First(L)) {
		P = Next(P);
		avg += Info(P);
		c++;
	}
	return (avg/c);
}

int main() {
	List L;
	CreateEmpty(&L);
	infotype TQi = 0;
	while (TQi <= 0) {
		scanf("%d", &TQi);
	}
	infotype TQ = TQi;
	//
	char in;
	int inEl;
	do {
		
		scanf("%s", &in);
		if (in == 'A') {
			scanf("%d", &inEl);
			if (inEl > 0) {
				InsVFirst(&L, inEl);
			}
		} else if (in == 'D') {
			
			DeleteRR(&L, TQ);
		} else if (in != 'F') {
			printf("Kode salah\n");
		}
	} while (in != 'F');
	//
	if (IsEmpty(L)) {
		printf("Proses selesai\n");
	} else {
		printf("%.2f\n", Average(L));
	}
}

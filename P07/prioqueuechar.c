/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: ADT Queue */
/* Deskripsi: ADT Priority Queue Char dengan representasi array secara eksplisit dan alokasi dinamik */
/* File: prioqueuechar.c */
/* Tanggal: 3 Oktober 2019 */

#include <stdio.h>
#include <stdlib.h>
#include "prioqueuechar.h"

/* ********* Prototype ********* */
boolean IsEmpty (PrioQueueChar Q) {
/* Mengirim true jika Q kosong: lihat definisi di atas */
	return Head(Q) == Nil && Tail(Q) == Nil;
}
boolean IsFull (PrioQueueChar Q) {
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
    return NBElmt(Q) == MaxEl(Q);
}
int NBElmt (PrioQueueChar Q) {
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
    if (IsEmpty(Q)) {
        return 0;
    } else {
        return  Tail(Q) - Head(Q) + (Tail(Q) < Head(Q) ? MaxEl(Q) : 0) + 1;
    }
}

/* *** Kreator *** */
void CreateEmpty (PrioQueueChar * Q, int Max) {
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
    (*Q).T = (infotype *) malloc ((Max+1) * sizeof(infotype));
    Head(*Q) = Nil;
    Tail(*Q) = Nil;
    MaxEl(*Q) = (*Q).T == NULL ? Nil : Max;
}

/* *** Destruktor *** */
void DeAlokasi(PrioQueueChar * Q) {
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
    free((*Q).T);
    MaxEl(*Q) = Nil;
}

/* *** Primitif Add/Delete *** */
void Add (PrioQueueChar * Q, infotype X) {
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut mengecil berdasarkan prio */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
        TAIL "maju" dengan mekanisme circular buffer; */
    if (IsEmpty(*Q)) {
        Head(*Q) = 1;
        Tail(*Q) = 1;
        Elmt(*Q, 1) = X;
    } else {
        address spot = Head(*Q);
        while ((Prio(Elmt(*Q, spot)) <= Prio(X)) && (spot != (Tail(*Q))%MaxEl(*Q)+1)) {
			spot = (spot % MaxEl(*Q)) + 1;
		}
		//
		address ri;
		for (int i = (Tail(*Q)-spot)%MaxEl(*Q); i >= 0; i--) {
			Elmt(*Q, (spot+i)%MaxEl(*Q)+1) = Elmt(*Q, (spot+i-1)%MaxEl(*Q)+1);
		}
		Elmt(*Q, spot) = X;
		//
		if (Tail(*Q) == MaxEl(*Q)) {
            Tail(*Q) = 1;
        } else {
            Tail(*Q)++;
        }
    }
}
void Del (PrioQueueChar * Q, infotype * X) {
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
    *X = InfoHead(*Q);
    //
    if (NBElmt(*Q) == 1) {
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    } else {
        if (Head(*Q) == MaxEl(*Q)) {
            Head(*Q) = 1;
        } else {
            Head(*Q)++;
        }
    }
}

/* Operasi Tambahan */
void PrintPrioQueueChar (PrioQueueChar Q) {
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<prio-1> <elemen-1>
...
<prio-n> <elemen-n>
#
*/
	address ri;
	if (!IsEmpty(Q)) {
		for (int i = 0; i < (Tail(Q)-Head(Q))%MaxEl(Q)+1; i++) {
			ri = (Head(Q)+i-1)%MaxEl(Q)+1;
			printf("%d %c\n", Prio(Elmt(Q, ri)), Info(Elmt(Q, ri)));
		}
	}
	printf("#\n");
}

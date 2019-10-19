/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: ADT Queue */
/* Deskripsi: ADT Priority Queue Char untuk menyelesaikan persoalan TPC/IP packet */
/* File: packet.c */
/* Tanggal: 3 Oktober 2019 */

#include <stdio.h>
#include "prioqueuechar.h"

int main() {
	int N;
	PrioQueueChar Q;
	int inPr;
	char inIn;
	infotype in, trash;
	//
	int prevPr = 1;
	scanf("%d", &N);
	CreateEmpty(&Q, N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %c", &inPr, &inIn);
		Prio(in) = inPr;
		Info(in) = inIn;
		Add(&Q, in);
		/*
		while((Prio(InfoHead(Q)) == prevPr) && (!IsEmpty(Q))) {
			printf("%d %c\n", i, Info(InfoHead(Q)));
			Del(&Q, &trash);
			prevPr++;
		}
		*/
		while((Prio(Elmt(Q, prevPr)) == prevPr)) {
			printf("%d %c\n", i, Info(Elmt(Q, prevPr)));
			prevPr++;
		}
	}
	//
	return 0;
}

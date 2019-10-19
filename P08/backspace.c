/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: ADT Stack */
/* Deskripsi: ADT Stack untuk menyelesaikan persoalan sequence pengetikan */
/* File: backspace.c */
/* Tanggal: 17 Oktober 2019 */

#include <stdio.h>
#include "stackt.h"
#include "boolean.h"

int main() {
	Stack A, B;
	int N, M;
	int in, tmpA, tmpB;
	CreateEmpty(&A);
	CreateEmpty(&B);
	//
	scanf("%d %d", &N, &M);
	//
	for (int i = 0; i < N; i++) {
		scanf("%d", &in);
		if (in == 0) {
			if (!IsEmpty(A)) {
				Pop(&A, &in);
			}
		} else {
			Push(&A, in);
		}
	}
	//
	for (int i = 0; i < M; i++) {
		scanf("%d", &in);
		if (in == 0) {
			if (!IsEmpty(B)) {
				Pop(&B, &in);
			}
		} else {
			Push(&B, in);
		}
	}
	//
	boolean same = true;
	while (same && (!IsEmpty(A) || !IsEmpty(B))) {
		Pop(&A, &tmpA);
		Pop(&B, &tmpB);
		if ((tmpA != tmpB) || (IsEmpty(A) && !IsEmpty(B)) || (IsEmpty(B) && !IsEmpty(A))) {
			same = false;
		}
	}
	if (same) {
		printf("Sama\n");
	} else {
		printf("Tidak sama\n");
	}
	//
	return 0;
}

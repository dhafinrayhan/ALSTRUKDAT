/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: ADT Stack */
/* Deskripsi: ADT Stack untuk menyelesaikan persoalan ekspresi postfix */
/* File: ekspresi.c */
/* Tanggal: 17 Oktober 2019 */

#include <stdio.h>
#include <math.h>
#include "mesintoken.h"
#include "stackt.h"
#include "boolean.h"

int main() {
	Stack S;
	CreateEmpty(&S);
	int op1, op2, opr;
	STARTTOKEN();
	//
	while (!EndToken) {
		if (CToken.tkn == 'b') {
			printf("%d\n", CToken.val);
			Push(&S, CToken.val);
		} else {
			Pop(&S, &op2);
			Pop(&S, &op1);
			printf("%d %c %d\n", op1, CToken.tkn, op2);
			if (CToken.tkn == '+') {
				opr = op1 + op2;
			} else if (CToken.tkn == '-') {
				opr = op1 - op2;
			} else if (CToken.tkn == '*') {
				opr = op1 * op2;
			} else if (CToken.tkn == '/') {
				opr = op1 / op2;
			} else {
				opr = pow(op1, op2);
			}
			Push(&S, opr);
			printf("%d\n", opr);
		}
		ADVTOKEN();
	}
	if (IsEmpty(S)) {
		printf("Ekspresi kosong\n");
	} else {
		Pop(&S, &opr);
		printf("Hasil=%d\n", opr);
	}
	//
	return 0;
}

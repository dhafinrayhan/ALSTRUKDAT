/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: Mesin */
/* Deskripsi: Mesin Token */
/* File: mesintoken.c */
/* Tanggal: 26 September 2019 */

#include <stdio.h>
#include "mesintoken.h"

boolean EndToken;
Token CToken;

void IgnoreBlank() {
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
    while (CC == BLANK) {
        ADV();
    }
}

void STARTTOKEN() {
/* I.S. : CC sembarang
   F.S. : EndToken = true, dan CC = MARK;
          atau EndToken = false, CToken adalah Token yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir Token */
    START();
    if (CC == MARK) {
        EndToken = true;
    } else {
        EndToken = false;
        IgnoreBlank();
        ADVTOKEN();
    }
}

void ADVTOKEN() {
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CToken adalah Token terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, maka EndToken = true
   Proses : Akuisisi kata menggunakan procedure SalinKata */
    if (CC == MARK) {
        EndToken = true;
    } else {
        SalinToken();
        IgnoreBlank();
    }
}

void SalinToken() {
/* Mengakuisisi Token dan menyimpan hasilnya dalam CToken
   I.S. : CC adalah karakter pertama dari Token
   F.S. : CToken berisi Token yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    //
    int toInt = CC;
    if ((toInt < 48) || (toInt > 57)) {
        CToken.tkn = CC;
        CToken.val = -1;
        ADV();
	} else {
        int valTkn = 0;
        CToken.tkn = 'b';
        while ((CC != MARK) && (CC != BLANK)) {
            toInt = CC;
            valTkn = 10*valTkn + toInt-48;
            ADV();
        }
        CToken.val = valTkn;
	}
}

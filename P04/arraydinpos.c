/* NIM: 13518063 */
/* Nama: Dhafin Rayhan Ahmad */
/* Topik: ADT */
/* Deskripsi: ADT ARRAY DINAMIK dan operasi-operasinya */
/* File: arraydinpos.c */
/* Tanggal: 12 September 2019 */

/* MODUL TABEL INTEGER */
/* Berisi definisi dan semua primitif pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi III : dengan banyaknya elemen didefinisikan secara implisit,
   memori tabel dinamik */

#include <stdio.h>
#include <stdlib.h>
#include "arraydinpos.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty(TabInt *T, int maxel) {
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel + 1 */
/* Proses: Inisialisasi semua elemen tabel T dengan ValUndef */
	TI(*T) = (ElType *) malloc ((maxel+1) * sizeof(ElType));
    MaxEl(*T) = maxel;
    for(IdxType i = GetFirstIdx(*T); i <= maxel; i++) {
		Elmt(*T, i) = ValUndef;
	}
}
void Dealokasi(TabInt *T) {
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T)=0; Neff(T)=0 */
	free(TI(*T));
    MaxEl(*T) = 0;
    Elmt(*T, IdxMin) = ValUndef;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmt(TabInt T) {
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
	int cN = 0;
	IdxType i = GetFirstIdx(T);
	while (Elmt(T, i) != ValUndef) {
		cN++;
		i++;
	}
	return cN;
}
/* *** Daya tampung container *** */
int MaxElement(TabInt T) {
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
	return MaxEl(T);
}
/* *** Selektor INDEKS *** */
IdxType GetFirstIdx(TabInt T) {
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
	return IdxMin;
}
IdxType GetLastIdx(TabInt T) {
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
	return NbElmt(T)-GetFirstIdx(T)+1;
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid(TabInt T, IdxType i) {
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
	return ((i >= IdxMin) && (i <= MaxEl(T)));
}
boolean IsIdxEff(TabInt T, IdxType i) {
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
    return ((i >= GetFirstIdx(T)) && (i <= GetLastIdx(T)));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty(TabInt T) {
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
    return (NbElmt(T) == 0);
}
/* *** Test tabel penuh *** */
boolean IsFull(TabInt T) {
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
    return (NbElmt(T) == MaxEl(T)-IdxMin+1);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi(TabInt *T) {
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
    int N;
    ElType inp;
    //
    do {
        scanf("%d", &N);
    } while (!((N >= 0) && (N <= MaxElement(*T))));
    //
    if (N == 0) {
        MakeEmpty(T, MaxEl(*T));
    } else {
		MakeEmpty(T, MaxEl(*T));
        Elmt(*T, N+1) = ValUndef;
        for (IdxType i = GetFirstIdx(*T); i <= N; i++) {
            scanf("%d", &inp);
            Elmt(*T, i) = inp;
        }
    }
}
void TulisIsiTab(TabInt T) {
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
    if (IsEmpty(T)) {
        printf("[]");
    } else {
        printf("[");
        for (IdxType i = GetFirstIdx(T); i < GetLastIdx(T); i++) {
            printf("%d,", Elmt(T, i));
        }
        printf("%d]", Elmt(T, GetLastIdx(T)));
    }
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika tabel : Penjumlahan, pengurangan, perkalian, ... *** */
TabInt PlusMinusTab(TabInt T1, TabInt T2, boolean plus) {
/* Prekondisi : T1 dan T2 memiliki Neff sama dan tidak kosong */
/*              Jika plus=false, tidak ada elemen T1-T2 yang menghasilkan nilai <= 0 */
/* Jika plus = true, mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */
    TabInt T3;
    MakeEmpty(&T3, MaxEl(T1));
    Elmt(T3, NbElmt(T1)+1) = ValUndef;
    //
    if (plus) {
        for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); i++) {
            Elmt(T3, i) = Elmt(T1, i) + Elmt(T2, i);
        }
    } else {
        for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); i++) {
            Elmt(T3, i) = Elmt(T1, i) - Elmt(T2, i);
        }
    }
    //
    return T3;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean IsEQ(TabInt T1, TabInt T2) {
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika Neff T1 = T2 dan semua elemennya sama */
    if (NbElmt(T1) == NbElmt(T2)) {
        for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); i++) {
            if (Elmt(T1, i) != Elmt(T2, i)) {
                return false;
            }
        }
    } else {
        return false;
    }
    //
    return true;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType Search1(TabInt T, ElType X) {
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
    for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++) {
        if (Elmt(T, i) == X) {
            return i;
        }
    }
    //
    return IdxUndef;
}
boolean SearchB(TabInt T, ElType X) {
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
    boolean Found = false;
    IdxType i = GetFirstIdx(T);
    //
    while ((!Found) && (i <= GetLastIdx(T))) {
        if (Elmt(T, i) == X) {
            Found = true;
        } else {
            i++;
        }
    }
    //
    return Found;
}

/* ********** NILAI EKSTREM ********** */
void MaxMin(TabInt T, ElType *Max, ElType *Min) {
/* I.S. Tabel T tidak kosong */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */
    ElType MaxF = Elmt(T, GetFirstIdx(T));
    ElType MinF = Elmt(T, GetFirstIdx(T));
    //
    for (IdxType i = GetFirstIdx(T)+1; i <= GetLastIdx(T); i++) {
        if (Elmt(T, i) > MaxF) {
            MaxF = Elmt(T, i);
        }
        if (Elmt(T, i) < MinF) {
            MinF = Elmt(T, i);
        }
    }
    //
    *Max = MaxF;
    *Min = MinF;
}

/* ********** OPERASI LAIN ********** */
void CopyTab(TabInt Tin, TabInt *Tout) {
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */
    TabInt ToutT;
    MakeEmpty(&ToutT, MaxElement(Tin));
    Elmt(ToutT, NbElmt(Tin)+1) = ValUndef;
    //
    for (IdxType i = GetFirstIdx(Tin); i <= GetLastIdx(Tin); i++) {
        Elmt(ToutT, i) = Elmt(Tin, i);
    }
    *Tout = ToutT;
}
ElType SumTab(TabInt T) {
/* Menghasilkan hasil penjumlahan semua elemen T */
/* Jika T kosong menghasilkan 0 */
    ElType sumT = 0;
    if (IsEmpty(T)) {
        return 0;
    } else {
        for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++) {
            sumT += Elmt(T, i);
        }
    }
    return sumT;
}
int CountX(TabInt T, ElType X) {
/* Menghasilkan berapa banyak kemunculan X di T */
/* Jika T kosong menghasilkan 0 */
    int count = 0;
    if (IsEmpty(T)) {
        return 0;
    } else {
        for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++) {
            if (Elmt(T, i) == X) {
                count++;
            }
        }
    }
    return count;
}
boolean IsAllGenap(TabInt T) {
/* Menghailkan true jika semua elemen T genap. T boleh kosong */
    if (IsEmpty(T)) {
        return false;
    } else {
        for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++) {
            if ((Elmt(T, i) % 2) != 0) {
                return false;
            }
        }
        //
        return true;
    }
}

/* ********** SORTING ********** */
void Sort(TabInt *T, boolean asc) {
/* I.S. T boleh kosong */
/* F.S. Jika asc = true, T terurut membesar */
/*      Jika asc = false, T terurut mengecil */
/* Proses : Mengurutkan T dengan salah satu algoritma sorting,
   algoritma bebas */
    if (asc) {
        ElType key;
        IdxType j;
        for (IdxType i = GetFirstIdx(*T)+1; i <= GetLastIdx(*T); i++) {
            key = Elmt(*T, i);
            j = i-1;
            //
            while ((j >= GetFirstIdx(*T)) && (Elmt(*T, j) > key)) {
                Elmt(*T, j+1) = Elmt(*T, j);
                j--;
            }
            //
            Elmt(*T, j+1) = key;
        }
    } else {
        IdxType iMax;
        ElType tmp;
        for (IdxType i = GetFirstIdx(*T); i < GetLastIdx(*T); i++) {
            iMax = i;
            //
            for (IdxType j = i+1; j <= GetLastIdx(*T); j++) {
                if (Elmt(*T, j) > Elmt(*T, iMax)) {
                    iMax = j;
                }
            }
            //
            tmp = Elmt(*T, iMax);
            Elmt(*T, iMax) = Elmt(*T, i);
            Elmt(*T, i) = tmp;
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl(TabInt *T, ElType X) {
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
    Elmt(*T, GetLastIdx(*T)+2) = ValUndef;
    Elmt(*T, GetLastIdx(*T)+1) = X;
}
/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl(TabInt *T, ElType *X) {
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
    *X = Elmt(*T, GetLastIdx(*T));
    Elmt(*T, GetLastIdx(*T)) = ValUndef;
}

/* ********* MENGUBAH UKURAN ARRAY ********* */
void GrowTab(TabInt *T, int num) {
/* Proses : Menambahkan max element sebanyak num */
/* I.S. Tabel sudah terdefinisi */
/* F.S. Ukuran tabel bertambah sebanyak num */
    TabInt Tc, Td;
    CopyTab(*T, &Tc);
    Dealokasi(T);
    MakeEmpty(T, MaxElement(Tc)+num);
    MakeEmpty(&Td, MaxElement(Tc)+num);
    //
    for (IdxType i = GetFirstIdx(Tc); i <= (GetLastIdx(Tc)); i++) {
        Elmt(Td, i) = Elmt(Tc, i);
    }
    //
    Elmt(Td, NbElmt(Tc)+1) = ValUndef;
    *T = Td;
}

void ShrinkTab(TabInt *T, int num) {
/* Proses : Mengurangi max element sebanyak num */
/* I.S. Tabel sudah terdefinisi, ukuran MaxEl > num, dan Neff < MaxEl - num. */
/* F.S. Ukuran tabel berkurang sebanyak num. */
    TabInt Tc, Td;
    CopyTab(*T, &Tc);
    Dealokasi(T);
    MakeEmpty(T, MaxElement(Tc)-num);
    MakeEmpty(&Td, MaxElement(Tc)-num);
    //
    for (IdxType i = GetFirstIdx(Tc); i <= (GetLastIdx(Tc)); i++) {
        Elmt(Td, i) = Elmt(Tc, i);
    }
    //
    Elmt(Td, NbElmt(Tc)+1) = ValUndef;
    *T = Td;
}

void CompactTab(TabInt *T) {
/* Proses : Mengurangi max element sehingga Neff = MaxEl */
/* I.S. Tabel tidak kosong */
/* F.S. Ukuran MaxEl = Neff */
    MaxEl(*T) = NbElmt(*T);
}

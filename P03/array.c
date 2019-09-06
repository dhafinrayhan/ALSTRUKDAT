/* MODUL TABEL INTEGER */
/* Berisi definisi dan semua primitif pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi I : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori tabel statik */

#include <stdio.h>
#include "array.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty (TabInt * T) {
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
    Neff(*T) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmt (TabInt T) {
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
    return Neff(T);
}
/* *** Daya tampung container *** */
int MaxNbEl (TabInt T) {
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
    return IdxMax;
}
/* *** Selektor INDEKS *** */
IdxType GetFirstIdx (TabInt T) {
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
    return IdxMin;
}
IdxType GetLastIdx (TabInt T) {
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
    return Neff(T);
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid (TabInt T, IdxType i) {
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
    return ((i >= IdxMin) && (i <= IdxMax));
}
boolean IsIdxEff (TabInt T, IdxType i) {
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
    return ((i >= GetFirstIdx(T)) && (i <= GetLastIdx(T)));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty (TabInt T) {
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
    return (Neff(T) == 0);
}
/* *** Test tabel penuh *** */
boolean IsFull (TabInt T) {
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
    return (Neff(T) == (IdxMax-IdxMin+1));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi (TabInt * T) {
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxNbEl(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxNbEl(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
    int N;
    ElType inp;
    //
    do {
        scanf("%d", &N);
    } while (!((N >= 0) && (N <= MaxNbEl(*T))));
    //
    if (N == 0) {
        MakeEmpty(T);
    } else {
        Neff(*T) = N;
        for (IdxType i = GetFirstIdx(*T); i <= GetLastIdx(*T); i++) {
            scanf("%d", &inp);
            Elmt(*T, i) = inp;
        }
    }
}
void BacaIsiTab (TabInt * T) {
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca elemen T sampai dimasukkan nilai -9999 */
/* Dibaca elemen satu per satu dan disimpan mulai dari IdxMin */
/* Pembacaan dihentikan jika pengguna memasukkan nilai -9999 */
/* Jika dari pertama dimasukkan nilai -9999 maka terbentuk T kosong */
    ElType inp;
    IdxType i = GetFirstIdx(*T);
    while (true) {
        if (i > MaxNbEl(*T)) {
            break;
        } else {
            scanf("%d", &inp);
            //
            if (inp == -9999) {
                break;
            } else {
                Elmt(*T, i) = inp;
                i++;
            }
        }
    }
    //
    Neff(*T) = i - 1;
}
void TulisIsi (TabInt T) {
/* Proses : Menuliskan isi tabel dengan traversal */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong : indeks dan elemen tabel ditulis berderet ke bawah */
/*      Jika T kosong : Hanya menulis "Tabel kosong" */
/* Contoh: Jika isi Tabel: [1, 20, 30, 50]
   Maka tercetak di layar:
   [1]1
   [2]20
   [3]30
   [4]50
*/
    if (IsEmpty(T)) {
        printf("Tabel kosong\n");
    } else {
        for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++) {
            printf("[%d]%d\n", i, Elmt(T, i));
        }
    }
}
void TulisIsiTab (TabInt T) {
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
TabInt PlusTab (TabInt T1, TabInt T2) {
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
    TabInt T3;
    Neff(T3) = Neff(T1);
    //
    for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); i++) {
        Elmt(T3, i) = Elmt(T1, i) + Elmt(T2, i);
    }
    //
    return T3;
}
TabInt MinusTab (TabInt T1, TabInt T2) {
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */
    TabInt T3;
    Neff(T3) = Neff(T1);
    //
    for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); i++) {
        Elmt(T3, i) = Elmt(T1, i) - Elmt(T2, i);
    }
    //
return T3;
}
TabInt KaliTab (TabInt T1, TabInt T2) {
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan T1 * T2 dengan definisi setiap elemen dengan indeks yang sama dikalikan */
    TabInt T3;
    Neff(T3) = Neff(T1);
    //
    for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); i++) {
        Elmt(T3, i) = Elmt(T1, i) * Elmt(T2, i);
    }
    //
    return T3;
}
TabInt KaliKons (TabInt Tin, ElType c) {
/* Prekondisi : Tin tidak kosong */
/* Mengirimkan tabel dengan setiap elemen Tin dikalikan c */
    for (IdxType i = GetFirstIdx(Tin); i <= GetLastIdx(Tin); i++) {
        Elmt(Tin, i) *= c;
    }
    //
    return Tin;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean IsEQ (TabInt T1, TabInt T2) {
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika ukuran T1 = T2 dan semua elemennya sama */
    if (Neff(T1) == Neff(T2)) {
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
boolean IsLess (TabInt T1, TabInt T2) {
/* Mengirimkan true jika T1 < T2, */
/* yaitu : sesuai dg analogi 'Ali' < Badu'; maka [0, 1] < [2, 3] */
    if (Neff(T1) <= Neff(T2)) {
        for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); i++) {
            if (Elmt(T1, i) < Elmt(T2, i)) {
                return true;
            } else if (Elmt(T1, i) > Elmt(T2, i)) {
                return false;
            }
        }
        //
        if (Neff(T1) < Neff(T2)) {
            return true;
        } else {
            return false;
        }
    } else {
        for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T2); i++) {
            if (Elmt(T1, i) < Elmt(T2, i)) {
                return true;
            } else if (Elmt(T1, i) > Elmt(T2, i)) {
                return false;
            }
        }
        //
        return false;
    }
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType Search1 (TabInt T, ElType X) {
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search TANPA boolean */
    for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++) {
        if (Elmt(T, i) == X) {
            return i;
        }
    }
    //
    return IdxUndef;
}
IdxType Search2 (TabInt T, ElType X) {
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search DENGAN boolean Found */
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
    if (Found) {
        return i;
    } else {
        return IdxUndef;
    }
}
boolean SearchB (TabInt T, ElType X) {
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Memakai Skema search DENGAN boolean */
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
boolean SearchSentinel (TabInt T, ElType X) {
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* dengan metoda sequential search dengan sentinel */
/* Untuk sentinel, manfaatkan indeks ke-0 dalam definisi array dalam Bahasa C
   yang tidak dipakai dalam definisi tabel */
    IdxType IdxFound;
    Elmt(T, 0) = X;
    //
    for (IdxType i = GetLastIdx(T); i >= 0; i--) {
        if (Elmt(T, i) == X) {
            IdxFound = i;
            break;
        }
    }
    //
    if (IdxFound == 0) {
        return false;
    } else {
        return true;
    }
}

/* ********** NILAI EKSTREM ********** */
ElType ValMax (TabInt T) {
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai maksimum tabel */
    ElType MaxEl = Elmt(T, GetFirstIdx(T));
    //
    for (IdxType i = GetFirstIdx(T)+1; i <= GetLastIdx(T); i++) {
        if (Elmt(T, i) > MaxEl) {
            MaxEl = Elmt(T, i);
        }
    }
    //
    return MaxEl;
}
ElType ValMin (TabInt T) {
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai minimum tabel */
    ElType MinEl = Elmt(T, GetFirstIdx(T));
    //
    for (IdxType i = GetFirstIdx(T)+1; i <= GetLastIdx(T); i++) {
        if (Elmt(T, i) < MinEl) {
            MinEl = Elmt(T, i);
        }
    }
    //
    return MinEl;
}
/* *** Mengirimkan indeks elemen bernilai ekstrem *** */
IdxType IdxMaxTab (TabInt T) {
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks i terkecil dengan nilai elemen merupakan nilai maksimum pada tabel */
    for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++) {
        if (Elmt(T, i) == ValMax(T)) {
            return i;
        }
    }
}
IdxType IdxMinTab (TabInt T) {
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks i terkecil dengan nilai elemen merupakan nilai minimum pada tabel */
    for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++) {
        if (Elmt(T, i) == ValMin(T)) {
            return i;
        }
    }
}

/* ********** OPERASI LAIN ********** */
void CopyTab (TabInt Tin, TabInt * Tout) {
/* I.S. Tin terdefinisi, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (elemen dan ukuran identik) */
/* Proses : Menyalin isi Tin ke Tout */
    Neff(*Tout) = Neff(Tin);
    //
    for (IdxType i = GetFirstIdx(Tin); i <= GetLastIdx(Tin); i++) {
        Elmt(*Tout, i) = Elmt(Tin, i);
    }
}
TabInt InverseTab (TabInt T) {
/* Menghasilkan tabel dengan urutan tempat yang terbalik, yaitu : */
/* elemen pertama menjadi terakhir, */
/* elemen kedua menjadi elemen sebelum terakhir, dst.. */
/* Tabel kosong menghasilkan tabel kosong */
    TabInt Ti;
    Neff(Ti) = Neff(T);
    //
    for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++) {
        Elmt(Ti, GetLastIdx(T)-i+1) = Elmt(T, i);
    }
    //
    return Ti;
}
boolean IsSimetris (TabInt T) {
/* Menghasilkan true jika tabel simetrik */
/* Tabel disebut simetrik jika: */
/*      elemen pertama = elemen terakhir, */
/*      elemen kedua = elemen sebelum terakhir, dan seterusnya */
/* Tabel kosong adalah tabel simetris */
    for (IdxType i = GetFirstIdx(T); i <= ((GetLastIdx(T)-GetFirstIdx(T)+1)/2); i++) {
        if (Elmt(T, i) != Elmt(T, GetLastIdx(T)-i+1)) {
            return false;
        }
    }
    //
    return true;
}

/* ********** SORTING ********** */
void MaxSortDesc (TabInt * T) {
/* I.S. T boleh kosong */
/* F.S. T elemennya terurut menurun dengan Maximum Sort */
/* Proses : mengurutkan T sehingga elemennya menurun/mengecil */
/*          tanpa menggunakan tabel kerja */
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
void InsSortAsc (TabInt * T) {
/* I.S. T boleh kosong */
/* F.S. T elemennya terurut menaik dengan Insertion Sort */
/* Proses : mengurutkan T sehingga elemennya menaik/membesar */
/*          tanpa menggunakan tabel kerja */
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
}

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl (TabInt * T, ElType X) {
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
    Neff(*T)++;
    Elmt(*T, GetLastIdx(*T)) = X;
}
void AddEli (TabInt * T, ElType X, IdxType i) {
/* Menambahkan X sebagai elemen ke-i tabel tanpa mengganggu kontiguitas
   terhadap elemen yang sudah ada */
/* I.S. Tabel tidak kosong dan tidak penuh */
/*      i adalah indeks yang valid. */
/* F.S. X adalah elemen ke-i T yang baru */
/* Proses : Geser elemen ke-i+1 s.d. terakhir */
/*          Isi elemen ke-i dengan X */
    Neff(*T)++;
    //
    for (IdxType j = GetLastIdx(*T); j > i; j--) {
        Elmt(*T, j) = Elmt(*T, j-1);
    }
    //
    Elmt(*T, i) = X;
}

/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl (TabInt * T, ElType * X) {
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
    *X = Elmt(*T, GetLastIdx(*T));
    Neff(*T)--;
}
void DelEli (TabInt * T, IdxType i, ElType * X) {
/* Menghapus elemen ke-i tabel tanpa mengganggu kontiguitas */
/* I.S. Tabel tidak kosong, i adalah indeks efektif yang valid */
/* F.S. X adalah nilai elemen ke-i T sebelum penghapusan */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
/* Proses : Geser elemen ke-i+1 s.d. elemen terakhir */
/*          Kurangi elemen efektif tabel */
    *X = Elmt(*T, i);
    //
    for (IdxType j = i; j <= GetLastIdx(*T)-1; j++) {
        Elmt(*T, j) = Elmt(*T, j+1);
    }
    //
    Neff(*T)--;
}

/* ********** TABEL DGN ELEMEN UNIK (SETIAP ELEMEN HANYA MUNCUL 1 KALI) ********** */
void AddElUnik (TabInt * T, ElType X) {
/* Menambahkan X sebagai elemen terakhir tabel, pada tabel dengan elemen unik */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/*      dan semua elemennya bernilai unik, tidak terurut */
/* F.S. Jika tabel belum penuh, menambahkan X sbg elemen terakhir T,
        jika belum ada elemen yang bernilai X.
    Jika sudah ada elemen tabel yang bernilai X maka I.S. = F.S.
    dan dituliskan pesan "nilai sudah ada" */
/* Proses : Cek keunikan dengan sequential search dengan sentinel */
/*          Kemudian tambahkan elemen jika belum ada */
    if (!SearchSentinel(*T, X)) {
        Neff(*T)++;
        Elmt(*T, GetLastIdx(*T)) = X;
    } else {
        printf("nilai sudah ada\n");
    }
}

/* ********** TABEL DGN ELEMEN TERURUT MEMBESAR ********** */
IdxType SearchUrut (TabInt T, ElType X) {
/* Prekondisi: Tabel T boleh kosong. Jika tidak kosong, elemen terurut membesar. */
/* Mengirimkan indeks di mana harga X dengan indeks terkecil diketemukan */
/* Mengirimkan IdxUndef jika tidak ada elemen tabel bernilai X */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel kosong */
    if (!IsEmpty(T)) {
        IdxType i = GetFirstIdx(T);
        //
        do {
            if (Elmt(T, i) == X) {
                return i;
            } else {
                i++;
            }
        } while ((Elmt(T, i) <= X) && (i <= GetLastIdx(T)));
    }
    //
    return IdxUndef;
}
ElType MaxUrut (TabInt T) {
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai maksimum pada tabel */
    return Elmt(T, GetLastIdx(T));
}
ElType MinUrut (TabInt T) {
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai minimum pada tabel*/
    return Elmt(T, GetFirstIdx(T));
}
void MaxMinUrut (TabInt T, ElType * Max, ElType * Min) {
/* I.S. Tabel T tidak kosong, elemen terurut membesar */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */
    *Max = MaxUrut(T);
    *Min = MinUrut(T);
}
void Add1Urut (TabInt * T, ElType X) {
/* Menambahkan X tanpa mengganggu keterurutan nilai dalam tabel */
/* Nilai dalam tabel tidak harus unik. */
/* I.S. Tabel T boleh kosong, boleh penuh. */
/*      Jika tabel isi, elemennya terurut membesar. */
/* F.S. Jika tabel belum penuh, menambahkan X. */
/*      Jika tabel penuh, maka tabel tetap. */
/* Proses : Search tempat yang tepat sambil geser */
/*          Insert X pada tempat yang tepat tersebut tanpa mengganggu keterurutan */
    if (!IsFull(*T)) {
        Neff(*T)++;
        IdxType i = GetLastIdx(*T);
        while ((X < Elmt(*T, i-1)) && (i > GetFirstIdx(*T))) {
            Elmt(*T, i) = Elmt(*T, i-1);
            i--;
        }
        Elmt(*T, i) = X;
    }
}
void Del1Urut (TabInt * T, ElType X) {
/* Menghapus X yang pertama kali (pada indeks terkecil) yang ditemukan */
/* I.S. Tabel tidak kosong */
/* F.S. Jika ada elemen tabel bernilai X , */
/*      maka banyaknya elemen tabel berkurang satu. */
/*      Jika tidak ada yang bernilai X, tabel tetap. */
/*      Setelah penghapusan, elemen tabel tetap kontigu! */
/* Proses : Search indeks ke-i dengan elemen ke-i = X. */
/*          Delete jika ada. */
    IdxType IdxFound = SearchUrut(*T, X);
    //
    if (IdxFound != IdxUndef) {
        DelEli(T, IdxFound, &X);
    }
}

#include <stdio.h>
#include "matriks.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M) {
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j) {
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
    return ((i >= BrsMin) && (i <= BrsMax) && (j >= KolMin) && (j <= KolMax));
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M) {
/* Mengirimkan indeks baris terkecil M */
    return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M) {
/* Mengirimkan indeks kolom terkecil M */
    return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M) {
/* Mengirimkan indeks baris terbesar M */
    return (BrsMin + NBrsEff(M) - 1);
}
indeks GetLastIdxKol (MATRIKS M) {
/* Mengirimkan indeks kolom terbesar M */
    return (KolMin + NKolEff(M) - 1);
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j) {
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
    return ((i >= GetFirstIdxBrs(M)) && (i <= GetLastIdxBrs(M)) && (j >= GetFirstIdxKol(M)) && (j <= GetLastIdxKol(M)));
}
ElType GetElmtDiagonal (MATRIKS M, indeks i) {
/* Mengirimkan elemen M(i,i) */
    return Elmt(M, i, i);
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl) {
/* Melakukan assignment MHsl  MIn */
    NBrsEff(*MHsl) = NBrsEff(MIn);
    NKolEff(*MHsl) = NKolEff(MIn);
    //
    for (indeks i = GetFirstIdxBrs(MIn); i <= GetLastIdxBrs(MIn); i++) {
        for (indeks j = GetFirstIdxKol(MIn); j <= GetLastIdxKol(MIn); j++) {
            Elmt(*MHsl, i, j) = Elmt(MIn, i, j);
        }
    }
}

/* ********** KELOMPOK BACA/TULIS ********** */
void BacaMATRIKS (MATRIKS * M, int NB, int NK) {
/* I.S. IsIdxValid(NB,NK) */
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
     MakeMATRIKS(NB, NK, M);
     //
     ElType inEl;
     for (indeks i = GetFirstIdxBrs(*M); i <= GetLastIdxBrs(*M); i++) {
         for (indeks j = GetFirstIdxKol(*M); j <= GetLastIdxKol(*M); j++) {
             scanf("%d", &inEl);
             Elmt(*M, i, j) = inEl;
         }
     }
}
void TulisMATRIKS (MATRIKS M) {
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
    for (indeks i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++) {
        for (indeks j = GetFirstIdxKol(M); j <= GetLastIdxKol(M)-1; j++) {
            printf("%d ", Elmt(M, i, j));
        }
        if (i < GetLastIdxBrs(M)) {
            printf("%d\n", Elmt(M, i, GetLastIdxKol(M)));
        } else {
            printf("%d", Elmt(M, i, GetLastIdxKol(M)));
        }
    }
}

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2) {
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */
    MATRIKS M3;
    MakeMATRIKS(NBrsEff(M1), NKolEff(M1), &M3);
    //
    for (indeks i = GetFirstIdxBrs(M3); i <= GetLastIdxBrs(M3); i++) {
        for (indeks j = GetFirstIdxKol(M3); j <= GetLastIdxKol(M3); j++) {
            Elmt(M3, i, j) = Elmt(M1, i, j) + Elmt(M2, i, j);
        }
    }
    //
    return M3;
}
MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2) {
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */
    MATRIKS M3;
    MakeMATRIKS(NBrsEff(M1), NKolEff(M1), &M3);
    //
    for (indeks i = GetFirstIdxBrs(M3); i <= GetLastIdxBrs(M3); i++) {
        for (indeks j = GetFirstIdxKol(M3); j <= GetLastIdxKol(M3); j++) {
            Elmt(M3, i, j) = Elmt(M1, i, j) - Elmt(M2, i, j);
        }
    }
    //
    return M3;
}
MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2) {
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
    MATRIKS M3;
    MakeMATRIKS(NBrsEff(M1), NKolEff(M2), &M3);
    //
    ElType El;
    for (indeks i = GetFirstIdxBrs(M3); i <= GetLastIdxBrs(M3); i++) {
        for (indeks j = GetFirstIdxKol(M3); j <= GetLastIdxKol(M3); j++) {
            El = 0;
            for (indeks k = GetFirstIdxKol(M1); k <= GetLastIdxKol(M1); k++) {
                El += Elmt(M1, i, k) * Elmt(M2, k, j);
            }
            Elmt(M3, i, j) = El;
        }
    }
    //
    return M3;
}
MATRIKS KaliKons (MATRIKS M, ElType X) {
/* Mengirim hasil perkalian setiap elemen M dengan X */
    MATRIKS MK;
    MakeMATRIKS(NBrsEff(M), NKolEff(M), &MK);
    //
    for (indeks i = GetFirstIdxBrs(MK); i <= GetLastIdxBrs(MK); i++) {
        for (indeks j = GetFirstIdxKol(MK); j <= GetLastIdxKol(MK); j++) {
            Elmt(MK, i, j) = X * Elmt(M, i, j);
        }
    }
    //
    return MK;
}
void PKaliKons (MATRIKS * M, ElType K) {
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */
    for (indeks i = GetFirstIdxBrs(*M); i <= GetLastIdxBrs(*M); i++) {
        for (indeks j = GetFirstIdxKol(*M); j <= GetLastIdxKol(*M); j++) {
            Elmt(*M, i, j) *= K;
        }
    }
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQ (MATRIKS M1, MATRIKS M2) {
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2)
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
    if ((NBrsEff(M1) != NBrsEff(M2)) || (NKolEff(M1) != NKolEff(M2))) {
        return false;
    } else {
        for (indeks i = GetFirstIdxBrs(M1); i <= GetLastIdxBrs(M1); i++) {
            for (indeks j = GetFirstIdxKol(M1); j <= GetLastIdxKol(M1); j++) {
                if (Elmt(M1, i, j) != Elmt(M2, i, j)) {
                    return false;
                }
            }
        }
        //
        return true;
    }
}
boolean NEQ (MATRIKS M1, MATRIKS M2) {
/* Mengirimkan true jika M1 tidak sama dengan M2 */
    return !(EQ(M1, M2));
}
boolean EQSize (MATRIKS M1, MATRIKS M2) {
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
    return ((NBrsEff(M1) == NBrsEff(M2)) && (NKolEff(M1) == NKolEff(M2)));
}

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M) {
/* Mengirimkan banyaknya elemen M */
    return (NBrsEff(M) * NKolEff(M));
}

/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M) {
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
    return (NBrsEff(M) == NKolEff(M));
}
boolean IsSimetri (MATRIKS M) {
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M)
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
    if (IsBujurSangkar(M)) {
        for (indeks i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++) {
            for (indeks j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++) {
                if (Elmt(M, i, j) != Elmt(M, j, i)) {
                    return false;
                }
            }
        }
        //
        return true;
    } else {
        return false;
    }
}
boolean IsSatuan (MATRIKS M) {
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
    if (IsBujurSangkar(M)) {
        for (indeks i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++) {
            for (indeks j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++) {
                if (i == j) {
                    if (GetElmtDiagonal(M, i) != 1) {
                        return false;
                    }
                } else {
                    if (Elmt(M, i, j) != 0) {
                        return false;
                    }
                }
            }
        }
        //
        return true;
    } else {
        return false;
    }
}
boolean IsSparse (MATRIKS M) {
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi:
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
    float count = 0;
    //
    for (indeks i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++) {
        for (indeks j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++) {
            if (Elmt(M, i, j) != 0) {
                count++;
            }
        }
    }
    //
    return ((count / NBElmt(M)) <= 0.05);
}
MATRIKS Inverse1 (MATRIKS M) {
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
    return KaliKons(M, -1);
}
float Determinan (MATRIKS M) {
/* Prekondisi: IsBujurSangkar(M) */
/* Menghitung nilai determinan M */
    float det = 0;
    //
    if (NBrsEff(M) == 1) {
        det = Elmt(M, GetFirstIdxBrs(M), GetFirstIdxKol(M));
    } else {
        indeks j = GetFirstIdxKol(M);
        for (indeks i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++) {
            MATRIKS Mi;
            MakeMATRIKS(NBrsEff(M)-1, NKolEff(M)-1, &Mi);
            //
            indeks iMi, jMi;
            //
            iMi = GetFirstIdxBrs(Mi);
            for (indeks iM = GetFirstIdxBrs(M); iM <= GetLastIdxBrs(M); iM++) {
                if (iM != i) {
                    jMi = GetFirstIdxKol(Mi);
                    for (indeks jM = GetFirstIdxKol(M); jM <= GetLastIdxKol(M); jM++) {
                        if (jM != j) {
                            Elmt(Mi, iMi, jMi) = Elmt(M, iM, jM);
                            jMi++;
                        }
                    }
                    iMi++;
                }
            }
            //
            det += (i % 2 == 1 ? 1: -1) * Elmt(M, i, j) * Determinan(Mi);
        }
    }
    //
    return det;
}
void PInverse1 (MATRIKS * M) {
/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
    PKaliKons(M, -1);
}
void Transpose (MATRIKS * M) {
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
    MATRIKS MT;
    MakeMATRIKS(NBrsEff(*M), NKolEff(*M), &MT);
    //
    for (indeks i = GetFirstIdxBrs(MT); i <= GetLastIdxBrs(MT); i++) {
        for (indeks j = GetFirstIdxKol(MT); j <= GetLastIdxKol(MT); j++) {
            Elmt(MT, i, j) = Elmt(*M, j, i);
        }
    }
    //
    *M = MT;
}

/* Operasi berbasis baris dan per kolom */
float RataBrs (MATRIKS M, indeks i) {
/* Menghasilkan rata-rata dari elemen pada baris ke-i */
/* Prekondisi: i adalah indeks baris efektif dari M */
    float r = 0;
    //
    for (indeks j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++) {
        r += Elmt(M, i, j);
    }
    //
    return (r / NKolEff(M));
}
float RataKol (MATRIKS M, indeks j) {
/* Menghasilkan rata-rata dari elemen pada kolom ke-j */
/* Prekondisi: j adalah indeks kolom efektif dari M */
    float r = 0;
    //
    for (indeks i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++) {
        r += Elmt(M, i, j);
    }
    //
    return (r / NBrsEff(M));
}
void MaxMinBrs (MATRIKS M, indeks i, ElType * max, ElType * min) {
/* I.S. i adalah indeks baris efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada baris i dari M
           min berisi elemen minimum pada baris i dari M */
    indeks jmax = GetFirstIdxKol(M);
    indeks jmin = GetFirstIdxKol(M);
    //
    for (indeks j = GetFirstIdxKol(M)+1; j <= GetLastIdxKol(M); j++) {
        if (Elmt(M, i, j) > Elmt(M, i, jmax)) {
            jmax = j;
        }
        if (Elmt(M, i, j) < Elmt(M, i, jmin)) {
            jmin = j;
        }
    }
    //
    *max = Elmt(M, i, jmax);
    *min = Elmt(M, i, jmin);
}
void MaxMinKol (MATRIKS M, indeks j, ElType * max, ElType * min) {
/* I.S. j adalah indeks kolom efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada kolom j dari M
           min berisi elemen minimum pada kolom j dari M */
    indeks imax = GetFirstIdxBrs(M);
    indeks imin = GetFirstIdxBrs(M);
    //
    for (indeks i = GetFirstIdxBrs(M)+1; i <= GetLastIdxBrs(M); i++) {
        if (Elmt(M, i, j) > Elmt(M, imax, j)) {
            imax = i;
        }
        if (Elmt(M, i, j) < Elmt(M, imin, j)) {
            imin = i;
        }
    }
    //
    *max = Elmt(M, imax, j);
    *min = Elmt(M, imin, j);
}
int CountXBrs (MATRIKS M, indeks i, ElType X) {
/* Menghasilkan banyaknya kemunculan X pada baris i dari M */
    int c = 0;
    //
    for (indeks j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++) {
        if (Elmt(M, i, j) == X) {
            c++;
        }
    }
    //
    return c;
}
int CountXKol (MATRIKS M, indeks j, ElType X) {
/* Menghasilkan banyaknya kemunculan X pada kolom j dari M */
    int c = 0;
    //
    for (indeks i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++) {
        if (Elmt(M, i, j) == X) {
            c++;
        }
    }
    //
    return c;
}

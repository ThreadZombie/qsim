/* questo file serve a implementare le funzioni definite nell'header matrice_complessa.h */

#include <stdio.h>
#include <stdlib.h>
#include "matrice_complessa.h"

#include "vettore_complesso.h"

//genera una matrice di complessi, prende il numero di vettori (righe) dela matrice in input
MatriceComplessa genera_matrice_complessa(int size) {
    MatriceComplessa mat;
    mat.size = size;
    mat.vettori = malloc(size * sizeof(VettoreComplesso));
    for (int i = 0; i < size; i++) {
        mat.vettori[i] = genera_vettore_complesso(size);  // ❗ deve inizializzare ogni riga
    }
    return mat;
}


void free_matrice_complessa(MatriceComplessa* mat) {
    if (mat->vettori != NULL) {
        for (int i = 0; i < mat->size; i++) {
            free_vettore_complesso(&mat->vettori[i]);  // usa la funzione esistente
        }
        free(mat->vettori);
        mat->vettori = NULL;
    }
    mat->size = 0;
}


void printa_matrice_complessa(MatriceComplessa* mat) {
    for (int i = 0; i < mat->size; i++) {
        printa_vettore_complesso(&mat->vettori[i]);
        printf("\n");
    }
}

MatriceComplessa molt_matrici(MatriceComplessa* a, MatriceComplessa* b, int q_len) {
    MatriceComplessa risultato = genera_matrice_complessa(q_len);

    for (int i = 0; i < q_len; i++) {
        for (int j = 0; j < q_len; j++) {
            Complesso somma;
            somma.real = 0;
            somma.img = 0;

            for (int k = 0; k < q_len; k++) {
                Complesso prod = molt_complessi(
                    a->vettori[i].complessi[k],
                    b->vettori[k].complessi[j]
                );
                somma = somma_complessi(somma, prod);
            }

            risultato.vettori[i].complessi[j] = somma;
        }
    }

    return risultato;
}

VettoreComplesso molt_mat_vet(MatriceComplessa* a, VettoreComplesso* b, int q_len) {
    VettoreComplesso risultato = genera_vettore_complesso(q_len);

    for (int i = 0; i < q_len; i++) {
        Complesso somma;
        somma.real = 0.0;
        somma.img = 0.0;

        for (int j = 0; j < q_len; j++) {
            Complesso m_ij = a->vettori[i].complessi[j];
            Complesso v_j = b->complessi[j];
            Complesso prodotto = molt_complessi(m_ij, v_j);
            somma = somma_complessi(somma, prodotto);
        }
        risultato.complessi[i] = somma;
    }

    return risultato;
}



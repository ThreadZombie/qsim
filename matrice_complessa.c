/* questo file serve a implementare le funzioni definite nell'header matrice_complessa.h */

#include <stdio.h>
#include <stdlib.h>
#include "matrice_complessa.h"

#include "vettore_complesso.h"

//genera una matrice di complessi, prende il numero di vettori (righe) dela matrice in input
MatriceComplessa genera_matrice_complessa(int size) {
    MatriceComplessa mat;
    mat.size = size;
    mat.vettori = malloc(sizeof(VettoreComplesso) * size); //allochiamo la memoria necessaria per il numero di righe richiesto
    if (mat.vettori == NULL) {
        printf("Errore: malloc fallita\n");
        exit(EXIT_FAILURE);
    }
}

void free_matrice_complessa(MatriceComplessa* mat) {
    free(mat->vettori);
    mat->vettori = NULL; //impostiamo vettori a NULL e size a 0 per evitare puntatori a memoria libera
    mat->size = 0;
}

void printa_matrice_complessa(MatriceComplessa* mat) {
    for (int i = 0; i < mat->size; i++) {
        printa_vettore_complesso(&mat->vettori[i]);
    }
}


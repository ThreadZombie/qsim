/* Questo gile header definisce la struct per rappresentare le matrici di numeri complessi, e le operazioni
 * principali da utilizzare sulle matrici */

#ifndef MATRICE_COMPLESSA_H
#define MATRICE_COMPLESSA_H

#include "vettore_complesso.h"

typedef struct {
    VettoreComplesso* vettori; //la matrice è un array di vettori complessi
    int size; //il numero di vettori nella matrice
} MatriceComplessa;

//funzione per generare una matrice complessa
MatriceComplessa genera_matrice_complessa(int size);

//funzione per liberare lo spazio occupato da una matrice complessa
void free_matrice_complessa(MatriceComplessa* mat);

void printa_matrice_complessa(MatriceComplessa* mat);

MatriceComplessa molt_matrici(MatriceComplessa* a, MatriceComplessa* b, int q_len);

VettoreComplesso molt_mat_vet(MatriceComplessa* a, VettoreComplesso* b, int q_len);

#endif

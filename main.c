#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "complessi.h"
#include "vettore_complesso.h"
#include "init_parser.h"
#include "matrice_complessa.h"
#include "circ_parser.h"
#include "util.h"

int main(void) {
    int qubits = parse_qubits("init-ex.txt");

    int q_len = (int)pow(2, qubits); //salviamo il valore q_len, cioè 2^n dove n è il numero di qubits, sarà usato sia per il numero di elementi del vettore che per il numero di elementi nella matrice (il numero di vettori, o righe, della matrice

    VettoreComplesso init_vet;

    init_vet = parse_init_vet("init-ex.txt", q_len); //prendiamo il vettore init dal file in input tramite la funzione di parsing

    //printf("qubits: %d, q_len: %d\n", qubits, q_len);
    printf("STATO INIZIALE:\n");
    printa_vettore_complesso(&init_vet);
    printf("\n");

    char circ[1024];
    parse_circ("circ-ex.txt", circ);

    //printf("%s\n", circ);

    int circ_len = strlen(circ);
    MatriceComplessa* mat_arr = malloc(sizeof(MatriceComplessa) * circ_len);

    parse_gate("circ-ex.txt", mat_arr, q_len, circ);

    /*
    for (int i = 0; i < circ_len; i++) {
        if (mat_arr[i].vettori == NULL) {
            printf("mat_arr[%d].vettori è NULL\n", i);
            continue;
        }
        printf("Matrice %d:\n", i);
        printa_matrice_complessa(&mat_arr[i]);
    }
    */


    MatriceComplessa prodotto = genera_matrice_complessa(q_len);

    // Inizializza tutti i valori della matrice a 1 + 0i
    for (int i = 0; i < q_len; i++) {
        for (int j = 0; j < q_len; j++) {
            if (i == j) {
                prodotto.vettori[i].complessi[j].real = 1.0;
                prodotto.vettori[i].complessi[j].img = 0.0;
            } else {
                prodotto.vettori[i].complessi[j].real = 0.0;
                prodotto.vettori[i].complessi[j].img = 0.0;
            }
        }
    }
// CIAOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO :)

    // Moltiplica iterativamente per ogni matrice in mat_arr
    for (int i = 0; i < circ_len; i++) {
        printf("fattore1 %d:\n", i);
        printa_matrice_complessa(&mat_arr[i]);
        printf("\n");
        printf("fattore2 %d:\n", i);
        printa_matrice_complessa(&prodotto);
        printf("\n");
        MatriceComplessa temp = molt_matrici(&mat_arr[i], &prodotto, q_len);
        free_matrice_complessa(&prodotto);  // libera memoria della matrice precedente
        prodotto = temp;                    // aggiorna il risultato con il nuovo prodotto
        printf("risultato %d:\n", i);
        printa_matrice_complessa(&prodotto);
    }

    // Stampa la matrice finale
    printf("PRODOTTO:\n");
    printa_matrice_complessa(&prodotto);

    VettoreComplesso vfin = molt_mat_vet(&prodotto, &init_vet, q_len);
    printf("STATO FINALE:\n");
    printa_vettore_complesso(&vfin);



    // Pulizia finale
    free_matrice_complessa(&prodotto);
    free(mat_arr);  // libera l'array di matrici (non i contenuti, che sono già stati gestiti)





    return 0;
}
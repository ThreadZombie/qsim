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

    printf("qubits: %d, q_len: %d\n", qubits, q_len);
    //printa_vettore_complesso(&init_vet);

    char circ[1024];
    parse_circ("circ-ex.txt", circ);

    //printf("%s\n", circ);

    int circ_len = strlen(circ);
    MatriceComplessa* mat_arr = malloc(sizeof(MatriceComplessa) * circ_len);

    parse_gate("circ-ex.txt", mat_arr, q_len, circ);

    Complesso c;
    parsa_numero_complesso("0+i", &c);
    //printa_complesso(c);

    return 0;
}
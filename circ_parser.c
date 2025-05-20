/* In questo file vengono implementate le funzioni di parsing del file circ.txt definite
 * nell'header circ_parser.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrice_complessa.h"
#include "util.h"

//funzione per ottenere il circuito di matrici, prende in input il file e restiuisce la stringa corrispondente al circuito #circ all'interno di dest
void parse_circ(char* filepath, char* dest) {
    char buffer[1024];
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("ERRORE NELLA LETTURA DEL FILE\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strncmp(buffer, "#circ", 5) == 0) {
            rimuovi_spazi(buffer);
            strcpy(dest, buffer + 5);
            size_t len = strlen(dest);
            if (len > 0 && dest[len - 1] == '\n') {
                dest[len - 1] = '\0';
            }
            return;
        }
    }
    printf("Errore: circuito non definito\n");
    fclose(fp);
    exit(EXIT_FAILURE);
}


//funzione per ottenere le matrici definite nel file circ.txt, prende in input il file e restituisce un array di matrici di complessi
void parse_gate(char* filepath, MatriceComplessa* mat_arr, int q_len, char* circ) {
    char buffer[1024];
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("ERRORE NELLA LETTURA DEL FILE\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; circ[i] != '\0'; i++) {
        char define[16];
        char gate[2];
        gate[0] = circ[i];
        gate[1] = '\0';
        sprintf(define, "#define %s", gate);
        rewind(fp);

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            if (strncmp(buffer, define, strlen(define)) == 0) {
                printf(&buffer);
            }
        }
    }
    return;

}

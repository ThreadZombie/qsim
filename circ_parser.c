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
void parse_gate(char* filepath, MatriceComplessa* mat_arr, int q_len, char* circ, int circ_len) {
    char buffer[1024];
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("ERRORE NELLA LETTURA DEL FILE\n");
        exit(EXIT_FAILURE);
    }

    int j = circ_len - 1;
    for (int i = 0; circ[i] != '\0'; i++) {
        char define[16];
        char gate[2];
        gate[0] = circ[i];
        gate[1] = '\0';
        sprintf(define, "#define %s", gate);
        rewind(fp);


        MatriceComplessa mat = genera_matrice_complessa(q_len); //avrà q_len righe

        int i_mat = 0;



        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            if (strncmp(buffer, define, strlen(define)) == 0) {
                char* strstart = strchr(buffer, '[');
                char* strend = strchr(buffer, ']');
                if (!strstart || !strend) {
                    printf("Errore: direttiva circ scritta in formato sbagliato\n");
                    exit(EXIT_FAILURE);
                }

                char tmp[1024];
                size_t len = strend - strstart - 1;
                strncpy(tmp, strstart + 1, len);
                tmp[len] = '\0';  // null-terminate manualmente
                int tmplen = strlen(tmp);
                rimuovi_spazi(tmp);
                //printf("%s\n", tmp);

                const char *p = tmp;
                int count = 0;

                while (*p && count < q_len) {
                    if (*p == '(') {
                        const char *start = p + 1;
                        const char *end = strchr(start, ')');

                        if (end) {
                            size_t len = end - start;
                            char *tuple_str = malloc(len + 1);

                            strncpy(tuple_str, start, len);
                            tuple_str[len] = '\0';

                            VettoreComplesso vet = genera_vettore_complesso(q_len); //inizializziamo il vettore che rappresenta la riga della matrice

                            parsa_vettore(&vet, tuple_str); //parsiamo i dati da mettere nel vettore

                            free_vettore_complesso(&mat.vettori[i_mat]);
                            mat.vettori[i_mat] = vet; //aggiungiamo il vettore alla matrice
                            i_mat++;

                            //printf("Tupla %d: %s\n", count, tuple_str);

                            free(tuple_str);
                            count++;
                            p = end + 1;

                        } else {
                            p++;
                        }
                    }
                }
            }
        }
        //printa_matrice_complessa(&mat);
        mat_arr[j] = mat;
        j--;



    }
    return;

}

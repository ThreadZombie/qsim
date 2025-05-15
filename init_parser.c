/*questo file implementa le funzioni definite nell'header init_parser.h
 *per prendere il file init in input e estrarne le informazioni sul numero
 *di qubits e sul vettore init*/

#include <stdio.h>
#include <string.h>
#include "init_parser.h"

#include <stdlib.h>

void rimuovi_spazi(char* str) {
    char* i = str;
    char* j = str;
    while (*j != 0) {
        if (*j != ' ') {
            *i = *j;
            i++;
        }
        j++;
    }
    *i = '\0';
}

int parse_qubits(char* filename) {
    char buffer[256];
    int qubits;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("ERRORE NELLA LETTURA DEL FILE (FILE NON TROVATO)\n");
        //richiama funzione iniziale
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strncmp(buffer, "#qubits", 7) == 0) {
            int i = 7;
            while (buffer[i] == ' ' || buffer[i] == '\t') {
                i++;
            }

            char qubits_str[100];
            int j = 0;

            while (buffer[i] != ' ' && buffer[i] != '\t'
                && buffer[i] != '\n' && buffer[i] != '\0') {
                qubits_str[j] = buffer[i];
                i++;
                j++;
                }
            qubits_str[j] = '\0';

            char *endptr;
            qubits = (int) strtol(qubits_str, &endptr, 10);

            if (*endptr != '\0') {
                printf("Errore: valore qubits non valido\n");
                fclose(fp);
                return -1;
            }

            fclose(fp);
            printf("numero di qubits: %d\n", qubits);
            return qubits;
        }
    }

    printf("Errore: direttiva #qubits non trovata\n");
    fclose(fp);
    return -1;

}

VettoreComplesso parse_init_vet(char* filename) {
    char buffer[1024];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("ERRORE NELLA LETTURA DEL FILE\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strncmp(buffer, "#init", 5) == 0) {
            char* strstart = strchr(buffer, '[');
            char* strend = strchr(buffer, ']');
            if (!strstart || !strend) {
                printf("Errore: direttiva init scritta in formato sbagliato\n");
                exit(EXIT_FAILURE);
            }

            char tmp[1024];
            size_t len = strend - strstart - 1;
            strncpy(tmp, strstart + 1, len);
            tmp[len] = '\0';  // null-terminate manualmente


            printf("%d\n", len);
            printf("%d\n", sizeof(tmp));



            int count = 1;
            for (int i = 0; i < len; i++) {
                if (tmp[i] == ',') {
                    count++;
                }
            }

            VettoreComplesso init_vet;
            init_vet = genera_vettore_complesso(count);
            rimuovi_spazi(tmp);
            printf("Dopo: '%s'\n", tmp);

            printf("tmp: '%s'\n", tmp);
            for (int i = 0; i < 30; i++) {
                printf("tmp[%d] = 0x%02x (%c)\n", i, (unsigned char)tmp[i],
                       (tmp[i] >= 32 && tmp[i] <= 126) ? tmp[i] : '.');
            }

            char *saveptr;
            char *token = strtok_r(tmp, ",", &saveptr);
            int i = 0;

            printf("qui ci arrivi\n");

            while (token) {
                printf("Token: '%s'\n", token);
                double real;
                double img;
                if (sscanf(token,"%lf+i%lf", &real, &img) == 2) {
                    //parsing riuscito
                    init_vet.complessi[i].real = real;
                    init_vet.complessi[i].img = img;
                    printf("fin qui tutto ok\n");
                }
                else if (sscanf(token, "%lf-i%lf", &real, &img) == 2) {
                    //parsing riuscito
                    init_vet.complessi[i].real = real;
                    init_vet.complessi[i].img = -img;
                }
                else {
                    printf("Errore: direttiva init definita erroneamente\n");
                    exit(EXIT_FAILURE);
                }
                i++;
                token = strtok_r(NULL, ",", &saveptr);

            }
            printa_vettore_complesso(&init_vet);
            return init_vet;
        }

    }


    printf("Errore: vettore init non trovato\n");
    exit(EXIT_FAILURE);
}
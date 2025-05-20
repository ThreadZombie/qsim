//implementazione delle funzioni nel file header util.h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "complessi.h"


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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//funzione delirante che gestisce i possibili formati di scrittura di un numero complesso (solo "0", o "0+1" 0 "0.5 + 10.5" ecc.)
void parsa_numero_complesso(const char* str, Complesso* c) {
    char* plus_ptr = strchr(str, '+');
    char* min_ptr = strchr(str + 1, '-');  // salta primo char, che può essere il segno della parte reale

    char* sep = plus_ptr ? plus_ptr : min_ptr; // il separatore è + o -

    if (sep != NULL && strchr(sep, 'i')) { // parte reale da inizio stringa a sep
        char real_part[64];
        strncpy(real_part, str, sep - str);
        real_part[sep - str] = '\0';

        char* img_part_str = sep; // parte immaginaria da sep fino a fine stringa
        double img_sign = (*img_part_str == '-') ? -1.0 : 1.0;
        img_part_str++; // Salta '+' o '-'

        if (*img_part_str == 'i') {
            if (*(img_part_str + 1) == '\0') { //se c'è solo i, la parte immaginaria sarà il segno moltiplicato per 1
                c->img = img_sign * 1.0;
            } else { //altrimenti prendiamo la parte dopo la i e la moltiplichiamo per il segno
                char* endptr;
                c->img = img_sign * strtod(img_part_str + 1, &endptr);
            }
        } else { //se non c'è la i mettiamo 0
            c->img = 0.0;
        }

        char* endptr;
        c->real = strtod(real_part, &endptr); //convertiamo la parte reale
    } else { //qui gestiamo il caso in cui ci sia solo la parte reale o solo la parte immaginaria
        if (strchr(str, 'i') == NULL) { //solo parte reale
            char* endptr;
            c->real = strtod(str, &endptr);
            c->img = 0.0;
        } else { //solo parte immaginaria
            c->real = 0.0;
            if (strcmp(str, "i") == 0) { //prima gestiamo i casi in cui c'è solo i o solo -i
                c->img = 1.0;
            } else if (strcmp(str, "-i") == 0) {
                c->img = -1.0;
            } else if (str[0] == 'i') { //gestiamo i casi in cui ci sia un valore "scalare" dopo la i
                c->img = strtod(str + 1, NULL);
            } else if (strncmp(str, "-i", 2) == 0) {
                c->img = -strtod(str + 2, NULL);
            } else {
                c->img = 0.0;
            }
        }
    }
}

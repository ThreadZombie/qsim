/* In questo file vengono implementate le operazioni
 * sui numeri complessi definite nel file header complessi.h */

#include <math.h>
#include "complessi.h"

Complesso somma_complessi(Complesso a, Complesso b) {
    Complesso risultato;
    risultato.real = a.real + b.real;
    risultato.img = a.img + b.img;
    return risultato;
}

Complesso molt_complessi(Complesso a, Complesso b) {
    Complesso risultato;
    risultato.real = (a.real * b.real) - (a.img * b.img);
    risultato.img = (a.real * b.img) + (a.img * b.real);
    return risultato;
}

double mod_complessi(Complesso a) {
    double risultato;
    risultato = sqrt((a.real * a.real) + (a.img * a.img));
    return risultato;
}
#include <stdio.h>
#include "complessi.h"
#include "init_parser.h"

void printa_complesso(Complesso c) {
    if (c.img < 0) {
        printf("%lf - i%lf\n", c.real, -c. img);
    } else {
        printf("%lf + i%lf\n", c.real, c.img);
    }
}

int main(void) {
    parse_qubits("init-ex.txt");
    parse_init_vet("init-ex.txt");
    return 0;
}
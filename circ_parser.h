/* In questo file header vengono definite le funzioni usate per il parsing del file di input circ.txt*/

#ifndef CIRC_PARSER_H
#define CIRC_PARSER_H

#include "matrice_complessa.h"

MatriceComplessa parse_gate(char* filepath);

char* parse_circ(char* filepath);

#endif
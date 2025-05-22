/* In questo file header vengono definite le funzioni usate per il parsing del file di input circ.txt*/

#ifndef CIRC_PARSER_H
#define CIRC_PARSER_H

#include "matrice_complessa.h"

void parse_circ(char* filepath, char* dest);

void parse_gate(char* filepath, MatriceComplessa* mat_arr, int q_len, char* circ, int circ_len);

#endif
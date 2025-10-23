#ifndef LINEA_H
#define LINEA_H

#include "definiciones.h"

typedef struct nodo_linea * Linea;

Linea crear_linea(char * texto);

char * texto_linea(Linea l);

void imprimir_linea(Linea l);

void destruir_linea(Linea l);

#endif

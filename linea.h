#ifndef LINEA_H
#define LINEA_H

#include "definiciones.h"

typedef struct nodo_linea * Linea;

Linea crear_linea(char * texto);

char * texto_linea(Linea l);

bool isEmpty(Linea l);

void imprimir_texto(Linea l);

void destruir_linea(Linea l);

#endif

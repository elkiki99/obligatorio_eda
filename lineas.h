#ifndef LINEAS_H
#define LINEAS_H

#include "linea.h"

typedef struct nodo_lineas * Lineas;

Lineas null();
// Devuelve lista vacía

Linea head(Lineas ls);
// Devuelve la primera línea

Lineas tail(Lineas ls);
// Devuelve el resto de la lista

bool isEmpty(Lineas ls);
// Retorna true si la lista está vacía

int cantidad_lineas(Lineas ls);
// Cantidad de líneas en la lista

void imprimir_lineas(Lineas ls);
// Imprime todas las líneas

int cantidad_lineas(Lineas ls);

Lineas insertar_linea_en_lista(Lineas ls, Linea nueva, unsigned int nroLinea);

// Inserta una línea en la posición nroLinea (1-indexed)

#endif

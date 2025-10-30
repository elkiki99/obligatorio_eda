#ifndef LINEAS_H
#define LINEAS_H

#include "linea.h"

typedef struct nodo_lineas * Lineas;

Lineas crear_lineas();
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

void imprimir_lineas_en_lista(Lineas ls);

int cantidad_lineas(Lineas ls);

Lineas insertar_linea_en_lista(Lineas ls, Linea nueva, unsigned int nroLinea);

Lineas borrar_linea_en_lista(Lineas ls, unsigned int nroLinea);

bool tienen_mismas_lineas(Lineas ls1, Lineas ls2);
//pre: no se pasan valores null

Lineas destruir_lineas(Lineas ls);

#endif

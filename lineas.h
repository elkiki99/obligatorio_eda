#ifndef LINEAS_H
#define LINEAS_H

#include "linea.h"

typedef struct nodo_lineas * Lineas;

Lineas crear_lineas();
// Devuelve lista vacía

Linea head(Lineas ls);
// Pre: ls no vacía.
// Devuelve la primera línea

Lineas tail(Lineas ls);
// Pre: ls no vacía.
// Devuelve el resto de la lista

int cantidad_lineas(Lineas ls);
// Cantidad de líneas en la lista

bool isEmpty(Lineas ls);
// retorna true si está vacía, false en caso contrario

void imprimir_lineas(Lineas ls, unsigned int nroLinea);
// imprime las lineas de una version

void imprimir_lineas_con_il(Lineas ls, unsigned int nroLinea);
// imprime lineas si la version es padre con "IL"

void imprimir_lineas_diferentes(Lineas padre, Lineas hija, unsigned int nroLinea);
// imprime las lineas diferentes de la hija con respecto a su padre

int cantidad_lineas(Lineas ls);
// imprime cantidad de lineas de la version

Lineas insertar_linea(Lineas ls, Linea nueva, unsigned int nroLinea);
// inserta linea en la versión

Lineas borrar_linea(Lineas ls, unsigned int nroLinea);
// elimina la linea de la version y engancha correctamente (lista encadenada)

bool tienen_mismas_lineas(Lineas ls1, Lineas ls2);
//pre: no se pasan valores null

Lineas destruir_lineas(Lineas ls);
// elimina las lineas y libera el espacio

#endif

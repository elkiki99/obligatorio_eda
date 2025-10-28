#ifndef VERSION_H
#define VERSION_H

#include "lineas.h"

#include "definiciones.h"

typedef struct nodo_version * Version;

Version crear_version(int num);
// Crea una nueva versión

int num_version(Version v);

void set_num_version(Version v, int nuevo_num);

Lineas lineas(Version v);
// Devuelve la lista de líneas de una versión

void insertar_linea_en_version(Version v, Linea nueva, int nroLinea);

void imprimir_lineas(Version v);
// imprimimos el texto

bool son_iguales(Version v1, Version v2);

#endif

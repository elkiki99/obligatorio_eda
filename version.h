#ifndef VERSION_H
#define VERSION_H

#include "lineas.h"
#include "definiciones.h"

typedef struct nodo_version * Version;

Version crear_version(int num);
// Crea una nueva versión

int num_version(Version v);
// devuelve el número de la versión

void set_num_version(Version v, int nuevo_num);
// setea el número de la versión

Lineas lineas(Version v);
// Devuelve la lista de líneas de una versión

void crear_e_insertar_linea(Version v, char * texto, unsigned int nroLinea);
// crea la linea y llama a la función en insertar_linea en lineas.c

bool son_iguales(Version v1, Version v2);
// verifica si dos versiones son iguales

void copiar_lineas(Version padre, Version hija);
// función recursiva que copia todas las líneas del padre al hijo

Linea copiar_linea(Linea original);
// copia una linea de texto en otra

Version destruir_version(Version v);
// destruye la versión, libera memoria y llama a destruir lineas

#endif

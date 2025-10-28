#ifndef VERSIONES_H
#define VERSIONES_H

#include "version.h"

typedef struct nodo_versiones * Versiones;

Versiones crear_versiones();
// Crea el árbol vacío de versiones

Version versiones_raiz(Versiones vs);
// Retorna la raiz del árbol versiones.
// Pre: versiones es no vacio.

Versiones versiones_ph(Versiones vs);
// Retorna el primer hijo del árbol versiones.
// Pre: versiones es no vacio.

Versiones versiones_sh(Versiones vs);
// Retorna el siguiente del árbol versiones.
// Pre: versiones es no vacio.

bool isEmpty(Versiones vs);
// Retorna true si a es vacio, false caso contrario.

int versiones_cantidad(Versiones vs);
// Retorna la cardinalidad de versiones.

int versiones_profundidad(Versiones vs);
// Retorna la profundidad del árbol versiones.

bool versiones_pertenece(Versiones vs, Version v);
// Retorna true si la versión pertenece al árbol versiones.

void versiones_imprimir_tree_aux(Versiones vs, int guiones);
// Imprime el árbol de versiones tabulado

void versiones_imprimir_tree (Versiones vs);
// Imprime el árbol de versiones tabulado

void versiones_imprimir_nivel (Versiones vs, int nivel);
// Imprime un nivel del árbol de versiones.

void versiones_imprimir_niveles (Versiones vs);
// Imprime todos los niveles del árbol de versiones.

void versiones_destruir (Versiones &vs);
// Destruye el árbol de versiones y lo deja apuntando a NULL.

bool versiones_insertar(Versiones &vs, char * path);
// Inserta el path en el arbol, por ejemplo si recibe "1.2.3" inserta "3" como hijo de "2" y nieto de "1"
// la rama "1.2" debe existir para insertar "3" correctamente.
// Pre: "vs" creado anteriormente.
// Retorna true si inserta correctamente, false en caso contrario

Versiones versiones_existe(Versiones vs, char * path);
// Devuelve la versión si existe, null caso contrario

void borrar_linea(Version v, unsigned int nroLinea);

void insertar_linea(Version v, char * texto, unsigned int nroLinea);

#endif

#ifndef VERSIONES_H
#define VERSIONES_H

#include "version.h"

typedef struct nodo_versiones * Versiones;

Versiones crear();
// Crea el árbol vacío de versiones

Version raiz(Versiones vs);
// Retorna la raiz del árbol versiones.
// Pre: versiones es no vacio.

Versiones ph(Versiones vs);
// Retorna el primer hijo del árbol versiones.
// Pre: versiones es no vacio.

Versiones sh(Versiones vs);
// Retorna el siguiente del árbol versiones.
// Pre: versiones es no vacio.

bool isEmpty(Versiones vs);
// Retorna true si a es vacio, false caso contrario.

bool versiones_pertenece(Versiones vs, Version v);
// Retorna true si la versión pertenece al árbol versiones.

void imprimir_tree_aux(Versiones vs, int espacios, char * padre);
// Imprime el árbol de versiones tabulado

void imprimir_tree(Versiones vs);
// Imprime el árbol de versiones tabulado

void versiones_destruir (Versiones &vs);
// Destruye el árbol de versiones y lo deja apuntando a NULL.

bool versiones_insertar(Versiones &vs, char * path);
// Inserta el path en el arbol, por ejemplo si recibe "1.2.3" inserta "3" como hijo de "2" y nieto de "1"
// la rama "1.2" debe existir para insertar "3" correctamente.
// Pre: "vs" creado anteriormente.
// Retorna true si inserta correctamente, false en caso contrario

Versiones tiene_padre(Versiones raiz, Versiones hija);

Versiones existe(Versiones vs, char * path);
// Devuelve la versión si existe, null caso contrario

void borrar_linea(Version v, unsigned int nroLinea);

void insertar_linea(Version v, char * texto, unsigned int nroLinea);

void borrar_nodo_versiones(Versiones &vs, char * path);

#endif

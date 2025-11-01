#include "archivo.h"
#include "versiones.h"
#include "version.h"
#include "lineas.h"
#include "linea.h"
#include <string.h>
#include <iostream>

using namespace std;

struct nodo_version {
	int num;
    Lineas ls;
};

Version crear_version(int num)
{
    Version v = new nodo_version;
    v->num = num;
    v->ls = crear_lineas(); // crea la lista de lineas vacía
     // apunta hacia null el primer elemento de la linea cuando creamos una nueva version
    return v;
}

int num_version(Version v) {
    return v->num;
}

void set_num_version(Version v, int nuevo_num)
{
    v->num = nuevo_num;
}

Lineas lineas(Version v)
{
    // Devuelve la lista de líneas de una versión (primer elemento de la lista)
    return v->ls;
}

void crear_e_insertar_linea(Version v, char * texto, unsigned int nroLinea)
{
    Linea nueva = crear_linea(texto);  // función en linea
    v->ls = insertar_linea(lineas(v), nueva, nroLinea); // funcion se encuentra en lineas.c
}

bool son_iguales(Version v1, Version v2)
{
    return tienen_mismas_lineas(lineas(v1), lineas(v2)); // implementada en lineas.c
}

void copiar_lineas(Version padre, Version hija)
{
    unsigned int i = 1;
    Lineas aux = padre->ls;

    while(aux != NULL)
    {
        // creamos una nueva linea (diferente a la que estamos copiando), mismo contenido, dif puntero
        Linea nueva = copiar_linea(head(aux));

        hija->ls = insertar_linea(hija->ls, nueva, i);
        aux = tail(aux);
        i++;
    }
}

Linea copiar_linea(Linea original)
{
    // Crear nueva lina con el mismo contenido q la linea original, devuelve la nueva linea (el puntero)
    Linea nueva = crear_linea(texto_linea(original));
    return nueva;
}

Version destruir_version(Version v)
{
    destruir_lineas(v->ls); // en lineas.c
    delete v;
    return NULL;
}







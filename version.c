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

//void insertar_linea_en_version(Version v, Linea nueva, int nroLinea)
//{
//    v->ls = insertar_linea_en_lista(lineas(v), nueva, nroLinea); // funcion se encuentra en lineas.c
//}

void imprimir_lineas(Version v)
{
    imprimir_lineas_en_lista(lineas(v)); // función se encuentra en lineas.c
}

void insertar_linea(Version v, char * texto, unsigned int nroLinea)
{
    Linea nueva = crear_linea(texto);  // función en linea
    v->ls = insertar_linea_en_lista(lineas(v), nueva, nroLinea); // funcion se encuentra en lineas.c
}

void borrar_linea(Version v, unsigned int nroLinea)
{
    v->ls = borrar_linea_en_lista(lineas(v), nroLinea); // función en lineas
}

bool son_iguales(Version v1, Version v2)
{
    return son_iguales_en_lista(lineas(v1), lineas(v2)); // implementada en lineas.c
}





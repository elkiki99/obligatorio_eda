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
    return tienen_mismas_lineas(lineas(v1), lineas(v2)); // implementada en lineas.c
}

void copiar_lineas(Version padre, Version hija)
{
    unsigned int i = 1;
    Lineas aux = padre->ls;

    while(aux != NULL)
    {
        hija->ls = insertar_linea_en_lista(hija->ls, head(aux), i);
        aux = tail(aux);
        i++;
    }
}

void imprimir_lineas_diferentes(Version padre, Version hija)
{
    Lineas ls_padre = lineas(padre);
    Lineas ls_hija = lineas(hija);

    if(son_iguales(padre, hija)) {
        cout << "No se realizaron modificaciones" << endl;
        return;
    }

    // si llegamos hasta aca, tenemos por ejemplo ls_padre = 1.2.3 y ls_hija 1.2.3.4 por ejemplo y sabemos que no son iguales
    while(ls_padre != NULL) { // avanzamos hasta que padre sea null, pero también avanzamos a la hija
        ls_padre = tail(ls_padre);
        ls_hija = tail(ls_hija);
    }

    while(ls_hija != NULL) // e imprimimos lo que quedó de la hija
    {
        imprimir_lineas_en_lista(ls_hija);
        ls_hija = tail(ls_hija);
    }
}

Version destruir_version(Version v)
{
    destruir_lineas(v->ls); // en lineas.c
    delete v;
    return NULL;
}







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
    v->ls = NULL;
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
    // Devuelve la lista de líneas de una versión
    return v->ls;
}

void insertar_linea_en_version(Version v, Linea nueva, int nroLinea)
{
    v->ls = insertar_linea_en_lista(lineas(v), nueva, nroLinea);
}






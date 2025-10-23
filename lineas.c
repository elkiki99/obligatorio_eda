#include "archivo.h"
#include "versiones.h"
#include "version.h"
#include "lineas.h"
#include "linea.h"
#include <string.h>
#include <iostream>

using namespace std;

struct nodo_lineas {
    Linea l;
    Lineas sig;
};

Lineas null()
{
    // Crea una lista vacía de líneas
    return NULL;
}

Linea head(Lineas ls)
{
    // Retorna el primer elemento (Linea) de la lista de líneas.
    // Pre: ls no vacía.
    return ls->l;
}

Lineas tail(Lineas ls)
{
    // Retorna el "resto" de la lista de líneas.
    // Pre: ls no vacía.
    return ls->sig;
}

bool isEmpty(Lineas ls)
{
    // Retorna true si la lista es vacía, false en caso contrario.
    return (ls == NULL);
}

int cantidad_lineas(Lineas ls)
{
    if (isEmpty(ls))
        return 0;
    else
        return 1 + cantidad_lineas(tail(ls));
}

void imprimir_lineas(Lineas ls)
{
    if (isEmpty(ls))
        return;
    else {
        imprimir_linea(head(ls));
        imprimir_lineas(tail(ls));
    }
}

Lineas insertar_linea_en_lista(Lineas ls, Linea nueva, unsigned int nroLinea)
{
    // Ver esta función. hay que implementar la funcionalidad de
    // que si ya existe la linea nroLinea, entonces mover las siguientes
    // hacia adelante y si no es la primera, enlazar la anterior a la nueva
    if (nroLinea == 1) {
        Lineas ls = new nodo_lineas;
        ls->l = nueva;
        ls->sig = ls;
        return ls;
    } else {
        ls->sig = insertar_linea_en_lista(ls->sig, nueva, nroLinea - 1);
        return ls;
    }
}

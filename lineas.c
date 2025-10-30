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

Lineas crear_lineas()
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

void imprimir_lineas_en_lista(Lineas ls)
{
    if (isEmpty(ls))
        return;
    else {
        imprimir_texto(head(ls));   // funcion que se encuentra en linea.c (imprime la linea de texto de la lista)
        imprimir_lineas_en_lista(tail(ls));   // llamada recursiva hasta llegar a null dentro de la lista
    }
}

Lineas insertar_linea_en_lista(Lineas ls, Linea nueva, unsigned int nroLinea)
{
    if (nroLinea == 1) {
        Lineas aux = new nodo_lineas;
        aux->l = nueva;
        aux->sig = ls;
        return aux;
    } else {
        ls->sig = insertar_linea_en_lista(ls->sig, nueva, nroLinea - 1); // arrancando desde la base, le restamos 1 hasta llegar
        return ls;
    }
}

Lineas borrar_linea_en_lista(Lineas ls, unsigned int nroLinea)
{
    if (nroLinea == 1) {
        Lineas aux = ls->sig;
        destruir_linea(ls->l);
        delete ls;
        return aux;
    }
    else {
        ls->sig = borrar_linea_en_lista(ls->sig, nroLinea - 1); // misma idea que en insertar linea
        return ls;
    }
}

bool tienen_mismas_lineas(Lineas ls1, Lineas ls2)
{
    if(isEmpty(ls1) && isEmpty(ls2))
        return true;
    else if(isEmpty(ls1))
        return false;
    else if(isEmpty(ls2))
        return false;
    else if (strcmp(texto_linea(head(ls1)), texto_linea(head(ls2))) == 0)
        return tienen_mismas_lineas(tail(ls1), tail(ls2));
    else
        return false;
}

Lineas destruir_lineas(Lineas ls)
{
    if (ls != NULL) {
        destruir_lineas(ls->sig);
        destruir_linea(ls->l); // lamada a funcion en linea.c
        delete ls;
    }
    return NULL;
}


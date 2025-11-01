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
    return NULL;
}

Linea head(Lineas ls)
{
    return ls->l;
}

Lineas tail(Lineas ls)
{
    return ls->sig;
}

bool isEmpty(Lineas ls)
{
    return (ls == NULL);
}

int cantidad_lineas(Lineas ls)
{
    if (isEmpty(ls))
        return 0;
    else
        return 1 + cantidad_lineas(tail(ls));
}

void imprimir_lineas(Lineas ls, unsigned int nroLinea)
{
    if (ls == NULL)
        return;
    else {
        cout << "\t\t" << nroLinea;
        imprimir_texto(head(ls));   // funcion que se encuentra en linea.c (imprime la linea de texto de la lista)
        imprimir_lineas(tail(ls), nroLinea + 1);   // llamada recursiva hasta llegar a null dentro de la lista
    }
}

void imprimir_lineas_con_il(Lineas ls, unsigned int nroLinea)
{
    if (isEmpty(ls))
        return;
    else {
        cout << "\t\tIL\t";
        cout << nroLinea;
        imprimir_texto(head(ls));   // funcion que se encuentra en linea.c (imprime la linea de texto de la lista)
        imprimir_lineas_con_il(tail(ls), nroLinea + 1);   // llamada recursiva hasta llegar a null dentro de la lista
    }
}

Lineas insertar_linea(Lineas ls, Linea nueva, unsigned int nroLinea)
{
    if (nroLinea == 1) {
        Lineas aux = new nodo_lineas;
        aux->l = nueva;
        aux->sig = ls;
        return aux;
    } else {
        ls->sig = insertar_linea(ls->sig, nueva, nroLinea - 1); // arrancando desde la base, le restamos 1 hasta llegar
        return ls;
    }
}

Lineas borrar_linea(Lineas ls, unsigned int nroLinea)
{
    if (nroLinea == 1) {
        Lineas aux = ls->sig;
        destruir_linea(ls->l);
        delete ls;
        return aux;
    }
    else {
        ls->sig = borrar_linea(ls->sig, nroLinea - 1); // misma idea que en insertar linea
        return ls;
    }
}

bool tienen_mismas_lineas(Lineas ls1, Lineas ls2)
{
    if(ls1 == NULL && ls2 == NULL)
        return true;
    else if(ls1 == NULL)
        return false;
    else if(ls2 == NULL)
        return false;
    else if (strcmp(texto_linea(head(ls1)), texto_linea(head(ls2))) == 0)
        return tienen_mismas_lineas(tail(ls1), tail(ls2));
    else
        return false;
}

void imprimir_lineas_diferentes(Lineas padre, Lineas hija, unsigned int nroLinea)
{
    if (isEmpty(padre) && isEmpty(hija))
        return;
    else if (isEmpty(padre)) {
        // esto significa que el hijo todavía tiene lineas
        cout << "\t\tIL\t" << nroLinea << "\t" << texto_linea(head(hija)) << endl;
        imprimir_lineas_diferentes(padre, tail(hija), nroLinea + 1);
    }
    else if (isEmpty(hija)) {
        // esto significa que el hijo borró lineas
        cout << "\t\tBL\t" << nroLinea << endl;
        imprimir_lineas_diferentes(tail(padre), hija, nroLinea + 1);
    }
    else if (strcmp(texto_linea(head(padre)), texto_linea(head(hija))) != 0) {
        // líneas diferentes, lo marcamos como borrado y como inserción?
        cout << "\t\tBL\t" << nroLinea << endl;
        cout << "\t\tIL\t" << nroLinea << "\t" << texto_linea(head(hija)) << endl;
        imprimir_lineas_diferentes(tail(padre), tail(hija), nroLinea + 1);
    }
    else {
        // son iguales, avanzamos
        imprimir_lineas_diferentes(tail(padre), tail(hija), nroLinea + 1);
    }
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


#include "archivo.h"
#include "versiones.h"
#include "version.h"
#include "lineas.h"
#include "linea.h"
#include <string.h>
#include <iostream>

using namespace std;

struct nodo_linea {
    char * texto;
};

// Crea una nueva línea a partir del texto recibido
Linea crear_linea(char * texto)
{
    Linea l = new nodo_linea;
    l->texto = new char[MAX_CONTENIDO];
    strcpy(l->texto, texto);
    return l;
}

// Retorna el texto de la línea
char * texto_linea(Linea l)
{
    return l->texto;
}

void imprimir_texto(Linea l)
{
    // Imprime el contenido de una línea
    cout << "\t" << texto_linea(l) << endl;
}

void destruir_linea(Linea l)
{
    delete[] l->texto;
    delete l;
}

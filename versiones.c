#include "archivo.h"
#include "versiones.h"
#include "version.h"
#include "lineas.h"
#include "linea.h"
#include <string.h>
#include <iostream>

using namespace std;

struct nodo_versiones {
	Version v;
	Versiones ph;
	Versiones sh;
};

Versiones crear_versiones()
{
    // Crea el árbol vacío de versiones
    return NULL;
}

Version versiones_raiz(Versiones vs)
{
    // Retorna la raiz del árbol versiones.
    // Pre: versiones es no vacio.
    return vs->v;
}

Versiones versiones_ph(Versiones vs)
{
    // Retorna el primer hijo del árbol versiones.
    // Pre: versiones es no vacio.
    return vs->ph;
}

Versiones versiones_sh(Versiones vs)
{
    // Retorna el siguiente del árbol versiones.
    // Pre: versiones es no vacio.
    return vs->sh;
}

bool isEmpty(Versiones vs)
{
    // Retorna true si a es vacio, false caso contrario.
    return (vs == NULL);
}

int versiones_cantidad(Versiones vs)
{
    // Retorna la cardinalidad de versiones.
    if(vs == NULL)
        return 0;
    else
        return 1 + versiones_cantidad(vs->ph) + versiones_cantidad(vs->sh);
}

int maximo(int x, int y)
{
    // Retorna el maximo de "x" e "y".
    if(x > y)
        return x;
    else
        return y;
}

int versiones_profundidad(Versiones vs)
{
    // Retorna la profundidad del árbol versiones.
    if(vs == NULL)
        return 0;
    else
        return maximo(1 + versiones_profundidad(vs->ph), versiones_profundidad(vs->sh));
}

bool versiones_pertenece(Versiones vs, Version v)
{
    // Retorna true si la versión pertenece al árbol versiones.
   if (vs == NULL)
		return false;
    else if(vs->v == v)
        return true;
	else
		return (versiones_pertenece(vs->ph, v) || versiones_pertenece(vs->sh, v));
}

void versiones_imprimir_tree_aux(Versiones vs, int espacios, int padre)
{
    // Imprime el árbol de versiones tabulado
	if (vs != NULL){
		for (int i = 0; i< espacios; i++)
			cout << "   ";

		if(padre == 0)
            cout << num_version(vs->v) << endl;
        else
            cout << padre << "." << num_version(vs->v) << endl;

		versiones_imprimir_tree_aux(vs->ph, espacios + 1, num_version(vs->v)); // pasamos el número del padre al hijo

		versiones_imprimir_tree_aux(vs->sh, espacios, padre); // mismo padre xa hermanos
	}
}

void versiones_imprimir_tree (Versiones vs)
{
    // Imprime el arbol de versiones tabulado
	versiones_imprimir_tree_aux(vs, 3, 0);
}

void versiones_destruir(Versiones &vs)
{
    // Destruye el árbol de versiones y lo deja apuntando a NULL.
	if (vs != NULL){
		versiones_destruir(vs->ph);
		versiones_destruir(vs->sh);
		delete vs;
	}
	vs = NULL;
}

bool versiones_insertar(Versiones &vs, char * path)
{
    Versiones aux, ant, iter_padre = NULL, temp, iter;
    char *pch = strtok(path, ".");
    int act;

    while (pch != NULL) {
        act = atoi(pch);                    // Número actual
        char *next_pch = strtok(NULL, "."); // Próximo token (nivel hijo)
        ant = NULL;

        // Determinamos 1er nodo
        if (iter_padre == NULL) {
            iter = vs;
        } else {
            iter = iter_padre->ph;
        }

        // Buscar posición correcta entre hermanos
        while (iter != NULL && num_version(iter->v) < act) {
            ant = iter;
            iter = iter->sh;
        }

        // No estamos en el último nivel
        if (next_pch != NULL) {
            if (iter != NULL && num_version(iter->v) == act) {
                iter_padre = iter; // Bajamos un nivel
            } else {
                return false; // Padre no existe
            }
        } else {
            // Último nivel
            // Validación para ver que no hayan huecos
            int max= 0; // máxima version hermana

            if (iter_padre == NULL) {
                temp = vs;
            } else {
                temp = iter_padre->ph;
            }

            while (temp != NULL) {
                int n = num_version(temp->v);
                if (n > max) {
                    max = n;
                }
                temp = temp->sh;
            }

            if (act > max + 1) {
                return false; // No tengo hermano anterior a la versión que queremos insertar (ej, 1.3 pero no hay 1.2)
            }

            // Correr hermanos si existen mayores
            if (iter != NULL && num_version(iter->v) >= act) {
                temp = iter;
                while (temp != NULL) {
                    set_num_version(temp->v, num_version(temp->v) + 1);
                    temp = temp->sh;
                }
            }

            // podemos crear nodo!
            aux = new nodo_versiones;
            aux->v = crear_version(act);
            aux->ph = NULL;
            aux->sh = NULL;

            // falta implementación. chequear si iter padre != NULL (es decir, la versión a insertar tiene padre)
            // chequear si la versión padre tiene lineas, y si tiene, copiarlas a la nueva versión
            if(iter_padre != NULL)
            {
                if()
            }

            // Insertar en orden entre hermanos
            if (ant == NULL) { // Primer hijo??
                // Entonces es el primer hermano del nivel
                if (iter_padre != NULL) { // estamos en primer nivel?
                    aux->sh = iter_padre->ph;
                    iter_padre->ph = aux;
                } else {
                    aux->sh = vs;
                    vs = aux;
                }
            } else {
                // no es el 1er hijo del nivel
                aux->sh = ant->sh;
                ant->sh = aux;
            }
            return true;
        }
        pch = next_pch;
    }
    return false;
}

Versiones versiones_existe(Versiones vs, char * path)
// Devuelve el nodo de versiones si existe, null caso contrario
{
    Versiones act = vs;
    int num = atoi(path);

    while (act != NULL && num_version(act->v) != num)
        act = act->sh;

    if (act == NULL)
        return NULL; // no existe

    // Seguimos al próximo número
    char * next_pch = strchr(path, '.');

    if (next_pch == NULL) {
        // No hay más niveles
        return act;
    } else
        return versiones_existe(act->ph, next_pch + 1);
}

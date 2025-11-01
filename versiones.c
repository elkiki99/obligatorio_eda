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

Versiones crear()
{
    return NULL;
}

Version raiz(Versiones vs)
{
    return vs->v;
}

Versiones ph(Versiones vs)
{
    // Retorna el primer hijo del árbol versiones.
    // Pre: versiones es no vacio.
    return vs->ph;
}

Versiones sh(Versiones vs)
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

Versiones existe(Versiones vs, char * path)
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
        return existe(act->ph, next_pch + 1);
}

Versiones tiene_padre(Versiones raiz, Versiones hija)
{
    if(raiz == NULL || raiz == hija) // si no hay raiz o es la hija (que pasamos por parámetro, es que no tiene padre o no hay)
        return NULL;

    if (raiz->ph == hija) // tiene padre y lo devolvemos
        return raiz;

    Versiones padre_en_hijos = tiene_padre(raiz->ph, hija); // llamada recursica

    if (padre_en_hijos != NULL)
        return padre_en_hijos;

    return tiene_padre(raiz->sh, hija);
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

void imprimir_tree_aux(Versiones vs, int espacios, char * padre)
{
    if (vs != NULL) {
        cout << "\t";

        for (int i = 0; i < espacios; i++)
            cout << "   ";

        char * actual = new char[MAX_CONTENIDO];
        actual[0] = '\0';

        char num[MAX_CONTENIDO]; // creamos num (aux)

        sprintf(num, "%d", num_version(vs->v)); //copiamos en num el número actual de la versión

        if (strlen(padre) == 0) { // si es el padre, imprimo el número actual
            strcpy(actual, num);
        } else {
            strcpy(actual, padre);  // else, copio el padre (num) a actual
            strcat(actual, ".");    // concateno punto
            strcat(actual, num);    // concateno el actual
        }

        cout << actual << endl; // imprimo el actual (ej 1.2)

        // función recursiva que imprime a los hijos
        imprimir_tree_aux(vs->ph, espacios + 1, actual);

        // función recursiva que imprime a los hermanos
        imprimir_tree_aux(vs->sh, espacios, padre);

        delete[] actual;
    }
}

void imprimir_tree(Versiones vs)
{
    // definimos el numero de padre como ""
    char * padre = new(char[MAX_CONTENIDO]);
    padre[0] = '\0'; // inicializamos el caracter, sino a veces imprime contenido basura

    // Imprime el arbol de versiones tabulado
	imprimir_tree_aux(vs, 3, padre);

	delete[] padre;
}

void versiones_destruir(Versiones &vs)
{
    // Destruye el árbol de versiones y lo deja apuntando a NULL.
	if (vs != NULL){
		versiones_destruir(vs->ph);
		versiones_destruir(vs->sh);
        destruir_version(vs->v); // esta función está en version.c, destruye el nodo a la versión
		delete vs;
	}
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
        if (iter_padre == NULL)
            iter = vs;
        else
            iter = iter_padre->ph;

        // Buscar posición correcta entre hermanos
        while (iter != NULL && num_version(iter->v) < act) {
            ant = iter;
            iter = iter->sh;
        }

        // No estamos en el último nivel
        if (next_pch != NULL) {
            if (iter != NULL && num_version(iter->v) == act)
                iter_padre = iter; // Bajamos un nivel
            else
                return false; // Padre no existe
        } else {
            // Último nivel
            // Validación para ver que no hayan huecos
            int max = 0; // máxima version hermana

            if (iter_padre == NULL)
                temp = vs;
            else
                temp = iter_padre->ph;

            while (temp != NULL) {
                int n = num_version(temp->v);
                if (n > max)
                    max = n;
                temp = temp->sh;
            }

            if (act > max + 1)
                return false; // No tengo hermano anterior a la versión que queremos insertar (ej, 1.3 pero no hay 1.2)

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
            aux->v = crear_version(act); // version implementada en version.c
            aux->ph = NULL;
            aux->sh = NULL;

            // chequear si la versión padre tiene lineas, y si tiene, copiarlas a la nueva versión
            // si es la primer versión del nivel ( ej: 1, 2, 5, ..) omitimos este paso
            if(iter_padre != NULL)
                copiar_lineas(iter_padre->v, aux->v); // version padre, version actual, funcion version (impementada en version.c)

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

void borrar_nodo_versiones(Versiones &vs, char * path)
{
    // esta función acepta la raíz del árbol versiones y la versión a eliminar
    // pre: la versión a eliminar existe (!= NULL)

    Versiones iter = vs, ant = NULL, iter_padre = NULL;
    char *pch = strtok(path, ".");
    //guarda el valor del path aqui para las llamadas recusrivas
    char path_hijo[MAX_CONTENIDO];
    int act;

    while (pch != NULL && iter != NULL) {
        act = atoi(pch);
        ant = NULL;

        // Buscar versión en el nivel actual
        while (iter != NULL && num_version(iter->v) < act) {
            ant = iter;
            iter = iter->sh;
        }

        char *next_pch = strtok(NULL, ".");

        if (next_pch != NULL) {
            // todavía no estamos en el último nivel asi que hay q bajar
            iter_padre = iter;
            iter = iter->ph;
            pch = next_pch;
        } else {
            // estamos en el nivel: borrar nodo

            // Si el nodo a borrar tiene hijos, hay qe eliminarlos recursivamente
            if (iter->ph != NULL) {
                while (iter->ph != NULL) {
                    // sprintf
                    sprintf(path_hijo, "%d", num_version(iter->ph->v)); //pasa de alpha a int (opuesto a atoi)
                    borrar_nodo_versiones(iter->ph, path_hijo);
                }
            }
            destruir_version(iter->v); // implementado en version.c (destruye version y lineas y linea)

            // Ajustar punteros
            if (ant == NULL) {
                // Era el primer hijo del nivel
                if (iter_padre != NULL)
                    iter_padre->ph = iter->sh;
                else
                    vs = iter->sh;
            } else {
                ant->sh = iter->sh;
            }

            Versiones sh = iter->sh;
            delete iter;

            // renombrarmos los hermanos 1 numero menos
            while(sh != NULL)
            {
                set_num_version(sh->v, num_version(sh->v) - 1);
                sh = sh->sh;
            }

            return;
        }
    }
}



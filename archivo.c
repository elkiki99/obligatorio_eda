#include "archivo.h"
#include "versiones.h"
#include "version.h"
#include "lineas.h"
#include "linea.h"
#include <string.h>
#include <iostream>

using namespace std;

struct nodo_archivo {
	char * nombre;
	Versiones vs;
};

Archivo CrearArchivo(char * nombre)
{
	Archivo a = new (nodo_archivo);
	a->nombre = new(char[MAX_NOMBRE]);
	strcpy(a->nombre, nombre);
	a->vs = crear(); // Crea el árbol de versiones vacío

	return a;
}

TipoRet BorrarArchivo(Archivo &a){
    // Elimina toda la memoria utilizada por el archivo y asigna NULL al puntero a.
    // Se asume como precondición que la referencia a un archivo (en particular a es distinto a NULL).
    // Esta operación se ejecuta al final de una sesión de trabajo con un archivo.
    versiones_destruir(a->vs); // en versiones.c (destruye el arbol de versiones)
    delete a;

	return OK;
}

TipoRet CrearVersion(Archivo &a, char * version, char * error)
{
    // Crea una nueva versión del archivo si la versión especificada cumple con las siguientes reglas:
    // - El padre de la nueva versión a crear ya debe existir. Por ejemplo, si creo la versión 2.15.1, la versión 2.15 ya debe existir.
    // Las versiones del primer nivel no siguen esta regla, ya que no tienen versión padre.
    // - No pueden quedar “huecos” entre versiones hermanas. Por ejemplo, si creamos la versión 2.15.3, las versiones 2.15.1 y 2.15.2 ya deben existir.
    // Ver ejemplo en la letra.

	cout << "VERSION A INSERTAR: " << version << endl;

	bool ok = versiones_insertar(a->vs, version);

    if (ok) {
        return OK;
    } else {
        strcpy(error, "No es posible insertar esta versión.");
        return ERROR;
    }
}

TipoRet BorrarVersion(Archivo &a, char * version, char * error){
// Elimina una versión del archivo si la version pasada por parámetro existe. En otro caso la operación quedará sin efecto.
// Si la versión a eliminar posee subversiones, éstas deberán ser eliminadas también, así como el texto asociado a cada una de las versiones.
// No deben quedar números de versiones libres sin usar. Por lo tanto cuando se elimina una versión, las versiones hermanas que le siguen deben decrementar su numeración (así también sus subversiones dependientes). Por ejemplo, si existen las versiones 2.15.1, 2.15.2 y 2.15.3, y elimino la 2.15.1, la versión 2.15.2 y la 2.15.3 pasan a ser 2.15.1 y 2.15.2 respectivamente, esto incluye a todas las subversiones de estas versiones.

    Versiones vs = existe(a->vs, version); // Existe la versión?

    if(!isEmpty(vs)) {
        borrar_nodo_versiones(a->vs, version); // función en versiones.c
        return OK;
    } else {
        strcpy(error, "La versión no existe");
        return ERROR;
    }
}

TipoRet MostrarVersiones(Archivo a){
// FORMATO: En primer lugar muestra el nombre del archivo. Después de una línea en blanco lista todos las versiones del archivo
// ordenadas por nivel jerárquico e indentadas según muestra el ejemplo publicado en la letra (cada nivel está indentado por un tabulador).

    cout << "\t\tSalida:" << endl;

    if(a->vs == NULL)
        cout << "\t\t\tNo hay versiones creadas" << endl;
    else
    {
        cout << "\t\t\t" << a->nombre << "\n" << endl;

        imprimir_tree(a->vs); // función implementada en versiones.c
    }

    return OK;
}

TipoRet InsertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea, char * error){
// Esta función inserta una linea de texto a la version parámetro en la posición nroLinea.
// El número de línea debe estar entre 1 y n+1, siendo n la cantidad de líneas del archivo. Por ejemplo, si el texto tiene 7 líneas, se podrá insertar en las posiciones 1 (al comienzo) a 8 (al final).
// Si se inserta en un número de línea existente, ésta y las siguientes líneas se correrán hacia adelante (abajo) dejando el espacio para la nueva línea.
// No se puede insertar una línea en una versión que tenga subversiones.
// Notar que el crear un archivo, éste no es editable hasta que no se crea al menos una versión del mismo. Sólo las versiones de un archivo son editables (se pueden insertar o suprimir líneas), siempre que no tengan subversiones creadas.
// En caso que TipoRet sea ERROR, en error se debe cargar cuál es el mismo.

    Versiones vs = existe(a->vs, version); // Existe la versión?

    if(isEmpty(vs)) {
        strcpy(error, "La versión no existe");
        return ERROR;
    }

    if(ph(vs) != NULL) // Tiene subversiones?
    {
        strcpy(error, "La versión no puede editarse ya que tiene subversiones");
        return ERROR;
    }


    //chequear numero de lineas no sea mayor a nroLinea + 1 y que sea mayor a 0
    if( (int) nroLinea > cantidad_lineas(lineas(raiz(vs))) + 1 || nroLinea < 1) { // si tiene 3 lineas y ponemos 1, 2, 3 o 4 funciona, pero 5 ya no
        strcpy(error, "El número de líneas es incorrecto");
        return ERROR;
    }

    // Si está todo bien... creamos la linea y la insertamos
    crear_e_insertar_linea(raiz(vs), linea, nroLinea); // función en version
    return OK;

	//return NO_IMPLEMENTADA;
}

TipoRet BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char * error){
// Esta función elimina una línea de texto de la version del archivo a en la posición nroLinea.
// El número de línea debe estar entre 1 y n, siendo n la cantidad de líneas del archivo. Por ejemplo, si el texto tiene 7 líneas, se podrán eliminar líneas de las posiciones 1 a 7.
// Cuando se elimina una línea, las siguientes líneas se corren, decrementando en una unidad sus posiciones para ocupar el lugar de la línea borrada.
// No se puede borrar una línea de una versión que tenga subversiones creadas.
// En caso que TipoRet sea ERROR, en error se debe cargar cuál es el mismo.

	Versiones vs = existe(a->vs, version); // Existe la versión?

    if(isEmpty(vs)) {
        strcpy(error, "La versión no existe");
        return ERROR;
    }

    if(ph(vs) != NULL) // Tiene subversiones?
    {
        strcpy(error, "La versión no puede editarse ya que tiene subversiones");
        return ERROR;
    }

    //chequear numero de lineas no sea mayor a nroLinea y que sea mayor a 0
    if( (int) nroLinea > cantidad_lineas(lineas(raiz(vs))) || nroLinea < 1) { // si tiene 3 lineas y ponemos 1, 2 o 3 funciona, pero 4 ya no
        strcpy(error, "El número de líneas es incorrecto");
        return ERROR;
    }

    // Si está todo bien... borramos la linea
    borrar_linea(lineas(raiz(vs)), nroLinea); // función en version
    return OK;
}

TipoRet MostrarTexto(Archivo a, char * version, char * error){
// Esta función muestra el texto completo de la version, teniendo en cuenta los cambios realizados en dicha versión y en las versiones ancestras, de la cual ella depende.

    cout << "\tSalida:" << endl;

    cout << "\t\t" << a->nombre << "\n" << endl;

    Versiones vs = existe(a->vs, version); // Existe la versión?

    if(!isEmpty(vs)) {
        // si existe, imprimir sus textos
        if(isEmpty(lineas(raiz(vs))))
            cout << "\t\tNo contiene lineas" << endl;
        else
            imprimir_lineas(lineas(raiz(vs)), 1); // función en lineas
        return OK;
    } else {
        strcpy(error, "La versión no existe");
        return ERROR;
    }
}

TipoRet MostrarCambios(Archivo a, char * version, char * error){
// Esta función muestra los cambios que se realizaron en el texto de la version parámetro, sin incluir los cambios realizados en las versiones ancestras de la cual dicha versión depende.

    Versiones vs = existe(a->vs, version); // Existe la versión?

    if(isEmpty(vs)) {
        strcpy(error, "La versión no existe");
        return ERROR;
    }

    cout << "\tSalida:" << endl;

    cout << "\t\t" << a->nombre << " - " << version << "\n" << endl;

    // necesitamos al padre si es que la version no es padre (ej 1), para después imprimir lo que no aparece en el padre
    Versiones padre = tiene_padre(a->vs, vs); // en version.c

    if(padre == NULL) { // no tiene padre poqlo que podemos mostrar todo eltexto
        imprimir_lineas_con_il(lineas(raiz(vs)), 1); // fucnion en lineas.c
    } else if(!son_iguales(raiz(padre), raiz(vs))) {
        imprimir_lineas_diferentes(lineas(raiz(padre)), lineas(raiz(vs)), 1); // imprime las diferentes partes
    } else {
        cout << "\t\tNo se realizaron modificaciones" << endl;
    }
	return OK;
}

TipoRet Iguales(Archivo a, char * version1, char * version2, bool &iguales, char * error){
// Esta función asigna al parámetro booleano (iguales) el valor true si ambas versiones (version1 y version2) del archivo tienen exactamente el mismo texto, y false en caso contrario.

    Versiones vs1 = existe(a->vs, version1); // Existe la versión 1?
    Versiones vs2 = existe(a->vs, version2); // Existe la versión 2?

    if(isEmpty(vs1) || isEmpty(vs2)) {
        strcpy(error, "Alguna de las 2 versiones no existe");
        return ERROR;
    }

    iguales = son_iguales(raiz(vs1), raiz(vs2)); // funcion en version.c

    if(iguales)
        strcpy(error, "Estas versiones son iguales");
    else
        strcpy(error, "Estas versiones son diferentes");

    return OK;

	//return NO_IMPLEMENTADA;
}

TipoRet VersionIndependiente(Archivo &a, char * version){
// Esta función crea una nueva versión al final del primer nivel con todos los cambios de la version especificada y de sus versiones ancestras. La versión que se crea debe ser independiente de cualquier otra versión.
// Por ejemplo, si creamos una versión independiente a partir de la 2.11.3, entonces se crea una nueva versión al final del primer nivel (si existen las versiones 1, 2, 3 y 4, entonces se crea la 5) con los cambios realizados a las versiones 2, 2.11 y 2.11.3.

	return NO_IMPLEMENTADA;
}

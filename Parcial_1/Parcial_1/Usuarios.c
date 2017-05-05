#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcionesAuxiliares.h"
#include "Usuarios.h"
#include "Publicaciones.h"
#include "Productos.h"
#include "Informes.h"


#define EL_DATO_ES_VALIDO 1
#define EL_DATO_NO_ES_VALIDO 0

#define EMPTY 0
#define USED 1
#define DELETED 2



/**
 * @brief Realiza la inicializacion del arrayUsuarios ingresando el valor EMPTY en el campo flagRegistro.
 * @param arrayUsuarios el array se pasa como parametro.
 * @param sizeArrayUsuarios el tamaño del array se pasa como parametro.
 * @return devuelve 1 si se pudo inicializar el array (o 0 si no se pudo porque se paso un tamaño del array invalido o un puntero NULO)
 */
int initArrayUsuarios(EUsuario* arrayUsuarios, int sizeArrayUsuarios)
{
    int i;
    int retorno=0;
    if ( arrayUsuarios==NULL || sizeArrayUsuarios<=0 )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
    {
        for (i=0; i<sizeArrayUsuarios; i++)
        {
            arrayUsuarios[i].flagRegistro=EMPTY;
            arrayUsuarios[i].id=0;
        }
        retorno=1;
    }
    return retorno;
}


/**
 * @brief Obtiene el primer indice libre del array.
 * @param arrayUsuarios el array se pasa como parametro.
 * @param sizeArrayUsuarios el tamaño del array se pasa como parametro.
 * @return devuelve el primer indice disponible (o -1 si no exite ninguno disponible o si el tamaño del array es invalido o un puntero NULO)
 */
int obtenerPosicionLibreArrayUsuarios(EUsuario* arrayUsuarios, int sizeArrayUsuarios)
{
    int i;
    if ( arrayUsuarios==NULL || sizeArrayUsuarios<=0 )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
    {
        for (i=0; i<sizeArrayUsuarios; i++)
            if (arrayUsuarios[i].flagRegistro==EMPTY)
                return i;
        printf("\n No se puede agregar usuario porque se agoto el espacio disponible! \n");
    }
    return -1;
}


/**
 * @brief busca si se encuentra cargado un id de usuario.
 * @param arrayUsuarios el array se pasa como parametro.
 * @param sizeArrayUsuarios el tamaño del array se pasa como parametro.
 * @param idUsuario se pasa como como parametro.
 * @return devuelve el indice en que esta guardado los datos de ese usuario (o -1 si no exite o si el tamaño del array es invalido o un puntero NULO)
 */
int buscarUsuarioPorId(EUsuario* arrayUsuarios, int sizeArrayUsuarios, int idUsuario)
{
    int i;
    if ( arrayUsuarios==NULL || sizeArrayUsuarios<=0 )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
        for (i=0; i<sizeArrayUsuarios; i++)
            if (arrayUsuarios[i].flagRegistro==USED && arrayUsuarios[i].id==idUsuario)
                return i;
    return -1;
}


/**
 * \brief Realiza el ingresdo de datos de un usuario
 * \param arrayUsuarios se le pasa como parametro el array-estructura donde se van a cargar los datos
 * \param sizeArrayUsuarios es el tamaño del array-estructura donde se van a guardar los datos
 * \return devuelve (0) si Tamaño invalido o puntero NULL pointer o sin espacio disponible - (1) si la carga se pudo realizar.
 */
int altaUsuario(EUsuario* arrayUsuarios, int sizeArrayUsuarios)
{
    EUsuario arrayAuxiliarUsuario[1]; /// es el array-estructura donde se van a guardar provisoriamente los datos
    int retorno=0;
    int existeUsuario;
    char salir='n';
    int indice = obtenerPosicionLibreArrayUsuarios(arrayUsuarios,sizeArrayUsuarios);

    while (salir!='s' && salir!='S' && indice!=-1)
    {
        arrayAuxiliarUsuario[0].id=calcularIdUsuario(arrayUsuarios,sizeArrayUsuarios);
        printf("\n El nro de id para el usuario a cargar es: %d \n",arrayAuxiliarUsuario[0].id);
        if(arrayAuxiliarUsuario[0].id>0)
        {
            cargaNombreYpasswordUsuario(arrayAuxiliarUsuario);
            arrayAuxiliarUsuario[0].flagRegistro=USED;
            arrayAuxiliarUsuario[0].contadorCalificaciones=0;
            arrayAuxiliarUsuario[0].acumuladorCalificaciones=0;

            arrayUsuarios[indice]=arrayAuxiliarUsuario[0];
            retorno=1;
            printf("\n El usuario ha sido cargado correctamente. \n");
            break;
        }
    }
    return retorno;
}


/**
 * \brief Realiza la modificacion de datos de un usuario
 * \param arrayUsuarios se le pasa como parametro el array-estructura donde se van a modificar los datos
 * \param sizeArrayUsuarios es el tamaño del array-estructura donde se van a guardar los datos
 * \return devuelve (0) si Tamaño invalido o puntero NULL pointer o si no se encuentra el usuario - (1) si la modificacion se pudo realizar.
 */
int modificarUsuarioPorId(EUsuario* arrayUsuarios, int sizeArrayUsuarios)
{
    EUsuario arrayAuxiliarUsuario[1]; /// es el array-estructura donde se van a guardar provisoriamente los datos
    int retorno=0;
    int existeUsuario;
    char salir='n';

    if ( existenUsuarios(arrayUsuarios, sizeArrayUsuarios)==0 )
    {
        printf("\n No se pueden modificar datos de usuarios porque no hay ninguno cargado! \n");
        salir='s';
    }
    while (salir!='s' && salir!='S')
    {
        arrayAuxiliarUsuario[0].id=ingresoIdUsuario();
        existeUsuario=buscarUsuarioPorId(arrayUsuarios,sizeArrayUsuarios,arrayAuxiliarUsuario[0].id);
        if(existeUsuario>=0)
        {
            cargaNombreYpasswordUsuario(arrayAuxiliarUsuario);
            strcpy(arrayUsuarios[existeUsuario].nombre,arrayAuxiliarUsuario[0].nombre);
            strcpy(arrayUsuarios[existeUsuario].password,arrayAuxiliarUsuario[0].password);
            retorno=1;
            printf("\n Se han modificado los datos correctamente. \n");
            break;
        }
        else
            getString("\n El nro. de id del usuario NO se encuentra ingresado! \
                \n Ingrese 'S' para salir de la carga de datos o cualquier otra tecla para continuar: ",&salir);
    }
    return retorno;
}


/**
 * \brief  Realiza la baja logica del registro de datos de un usuario.
 * \param arrayUsuarios se le pasa como parametro el array-estructura donde se encuentra el usuario cuyos datos se quieren dar de baja.
 * \param sizeArrayUsuarios es el tamaño del array-estructura donde se van a guardar los datos
 * \return devuelve (0) si Tamaño invalido o puntero NULL pointer o si no se encuentra el usuario - (1) si la baja se pudo realizar.
 */
int bajaUsuarioPorId(EUsuario* arrayUsuarios, int sizeArrayUsuarios, EProducto* arrayProductos, int sizeArrayProductos)
{
    EUsuario arrayAuxiliarUsuario[1]; /// es el array-estructura donde se van a guardar provisoriamente los datos
    int retorno=0;
    int existeUsuario;
    char salir='n';

    if ( existenUsuarios(arrayUsuarios, sizeArrayUsuarios)==0 )
    {
        printf("\n No se puede eliminar un usuario porque no hay ninguno cargado! \n");
        salir='s';
    }
    while (salir!='s' && salir!='S')
    {
        arrayAuxiliarUsuario[0].id=ingresoIdUsuario();
        existeUsuario=buscarUsuarioPorId(arrayUsuarios,sizeArrayUsuarios,arrayAuxiliarUsuario[0].id);
        if(existeUsuario>=0)
        {
            retorno=1;
            arrayUsuarios[existeUsuario].flagRegistro=DELETED;
            eliminarProductosPorBajaUsuario(arrayProductos,sizeArrayProductos,arrayUsuarios[existeUsuario].id);
            printf("\n El usuario id nro. %d  ha sido dado de baja correctamente. \n", arrayAuxiliarUsuario[0].id);
            break;
        }
        else
            getString("\n El nro. de id del usuario NO se encuentra ingresado! \
                \n Ingrese 'S' para salir de la carga de datos o cualquier otra tecla para continuar: ",&salir);
    }
    return retorno;
}


/**
 * @brief pide al usuario el id del usuario y lo devuelve validado dentro de un rango de enteros.
 * @param no recibe parametros.
 * @return el numero validado como int.
 */
int ingresoIdUsuario()
{
    int idUsuario;
    getInt(&idUsuario, "\n Ingrese el id del usuario: ", "\n El dato ingresado es invalido!\
        \n El id debe ser un numero positvo entre 1 y 31999",1,1,1,1,31999);
    return idUsuario;
}


/**
 * @brief cacula el proximo numero de id de usuario en una secuencia autoincrementable.
 * @param arrayUsuarios el array se pasa como parametro.
 * @param sizeArrayUsuarios el tamaño del array se pasa como parametro.
 * @return devuelve el proximo id (o -1 si no exite ninguno disponible o si el tamaño del array es invalido o un puntero NULO)
 */
int calcularIdUsuario(EUsuario* arrayUsuarios, int sizeArrayUsuarios)
{
    int nextIdUsuario=0;
    int i;
    if ( arrayUsuarios==NULL || sizeArrayUsuarios<=0 )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
        for (i=0; i<sizeArrayUsuarios; i++)
            if ( i==0 || ( arrayUsuarios[i].flagRegistro==USED && arrayUsuarios[i].id>=nextIdUsuario ) )
                nextIdUsuario=arrayUsuarios[i].id+1;
    return nextIdUsuario;
}


/**
 * @brief cacula si el array de usuarios no está vacio
 * @param arrayUsuarios el array se pasa como parametro.
 * @param sizeArrayUsuarios el tamaño del array se pasa como parametro.
 * @return devuelve 0 si no exite ningun usuario cargado o si el tamaño del array es invalido o un puntero NULO), de lo contrario devuelve 1.
 */
int existenUsuarios(EUsuario* arrayUsuarios, int sizeArrayUsuarios)
{
    int i;
    int retorno=0;
    if ( arrayUsuarios==NULL || sizeArrayUsuarios<=0 )
        printf("\n La ejecucion se detendra! Tamaño de array invalido o puntero NULO \n");
    else
        for (i=0; i<sizeArrayUsuarios; i++)
            if ( arrayUsuarios[i].flagRegistro==USED )
            {
                retorno=1;
                break;
            }
    return retorno;
}


/**
 * @brief pide al usuario los datos de nombre y password del usuario y los carga (validados) en un array auxiliar recibido como parametro.
 * @param arrayAuxiliar el array se pasa como parametro.
 * @return no devuelve nada.
 */
void cargaNombreYpasswordUsuario(EUsuario* arrayAuxiliarUsuario)
{
    char arrayCharsAdmitidos[1]="-";
    getType("\n Ingrese el nombre del usuario: ", "\n El dato ingresado es invalido!\
        \n Solo se adminten letras, numeros, el caracter '-' y que no exceda los 49 caracteres \n",1,2,arrayCharsAdmitidos,49,arrayAuxiliarUsuario[0].nombre);
    getType("\n Ingrese el password del usuario: ", "\n El dato ingresado es invalido!\
        \n Solo se adminten letras, numeros, el caracter '-' y que no exceda los 49 caracteres \n",1,2,arrayCharsAdmitidos,49,arrayAuxiliarUsuario[0].password);

}


/**
 * @brief muetra por pantalla un listado con los usuarios.
 * @param arrayUsuarios el array se pasa como parametro.
 * @param sizeArrayUsuarios el tamaño del array se pasa como parametro.
 * @return no devuelve nada.
 */
void listarUsuarios(EUsuario* arrayUsuarios, int sizeArrayUsuarios)
{
    int i;
    for (i=0; i<sizeArrayUsuarios; i++)
        if (arrayUsuarios[i].flagRegistro!=EMPTY && arrayUsuarios[i].contadorCalificaciones!=0)
            printf("\n Id %d - Nombre: %s - Promedio Calificaciones: %.2f - Cantidad Calificaciones: %d - CalifAcum: %d - FlagRegistro %d\
                   ", arrayUsuarios[i].id, arrayUsuarios[i].nombre, arrayUsuarios[i].acumuladorCalificaciones/arrayUsuarios[i].contadorCalificaciones, arrayUsuarios[i].flagRegistro);
    printf("\n");
}

/*
void cargaAutomaticausuarios(EUsuario* arrayUsuarios, int sizeArrayUsuarios)
{
    arrayUsuarios[0].id=1;
    arrayUsuarios[0].numero=10;
    strcpy(arrayUsuarios[0].nombre,"AAA");
    strcpy(arrayUsuarios[0].password,"AAA");
    arrayUsuarios[0].contadorLlamadas=0;
    arrayUsuarios[0].flagRegistro=USED;

    arrayUsuarios[1].id=2;
    arrayUsuarios[1].numero=20;
    strcpy(arrayUsuarios[1].nombre,"CCC");
    strcpy(arrayUsuarios[1].password,"CCC");
    arrayUsuarios[1].contadorLlamadas=0;
    arrayUsuarios[1].flagRegistro=USED;

    arrayUsuarios[2].id=3;
    arrayUsuarios[2].numero=30;
    strcpy(arrayUsuarios[2].nombre,"BBB");
    strcpy(arrayUsuarios[2].password,"BBB");
    arrayUsuarios[2].contadorLlamadas=0;
    arrayUsuarios[2].flagRegistro=USED;

}


*/



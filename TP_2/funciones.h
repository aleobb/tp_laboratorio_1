#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

struct
{
    char nombre[50];
    int edad;
    int estado;
    long int dni;

}typedef EPersona;

/**
 * @brief Obtiene el primer indice libre del array.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tama�o del array se pasa como parametro.
 * @return devuelve el primer indice disponible (o -1 si no exite ninguno disponible)
 */
int obtenerEspacioLibre(EPersona arrayPersonas[], int sizeArray);



/**
 * @brief Obtiene el indice que coincide con el dni pasado por parametro.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tama�o del array se pasa como parametro.
 * @param dni: a ser buscado en el array.
 * @return el indice en donde se encuentra el elemento que coincide con el parametro dni (o -1 si no lo encuentra)
 */
int buscarPorDni(EPersona arrayPersonas[], int sizeArray, long int dni);



/**
 * @brief Realiza el ingresdo de datos de una persona.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tama�o del array se pasa como parametro.
 * @return devuelve 1 (EL_DATO_ES_VALIDO) si el ingreso se pudo realizar correctamente.
 */
int ingresoPersona(EPersona arrayPersonas[],int sizeArray);



/**
 * @brief Realiza la modificacion de datos de una persona.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tama�o del array se pasa como parametro.
 * @return devuelve 1 (EL_DATO_ES_VALIDO) si la modificacion se pudo realizar correctamente.
 */
int modificacionPersona(EPersona arrayPersonas[], int sizeArray);


/**
 * @brief Realiza la baja logica del registro de datos de una persona.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tama�o del array se pasa como parametro.
 * @return devuelve 1 (EL_DATO_ES_VALIDO) si la baja se pudo realizar correctamente.
 */
int eliminarPersona(EPersona arrayPersonas[], int sizeArray);


/**
 * @brief pide al usuario el dni de la persona y lo devuelve validado.
 * @param no recibe parametros.
 * @return el dni validado como long int.
 */
long int ingresoDNI();


/**
 * @brief pide al usuario los datos de nombre y edad de la persona y los carga (validados) en un array auxiliar recibido como parametro.
 * @param arrayAuxiliar el array se pasa como parametro.
 * @return no devuelve nada.
 */
void ingresoDatos(EPersona arrayAuxiliar[]);


/**
 * @brief Realiza la inicializacion del arrayPersonas ingresando el valor -1 en el campo estado.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tama�o del array se pasa como parametro.
 * @return no devuelve nada.
 */
void initArray(EPersona arrayPersonas[],int sizeArray);


/**
 * @brief muetra por pantalla un listado con las personas ordenadas por nombre.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tama�o del array se pasa como parametro.
 * @return no devuelve nada.
 */
void listarPorNombre(EPersona arrayPersonas[], int sizeArray);


/**
 * @brief ordena el array de personas por nombre.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tama�o del array se pasa como parametro.
 * @return no devuelve nada.
 */
void ordenarPorNombre(EPersona arrayPersonas[], int sizeArray);


/**
 * @brief muetra un grafico por pantalla con la cantidad de personas por grupos de edades.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tama�o del array se pasa como parametro.
 * @return no devuelve nada.
 */
void graficoEdades(EPersona arrayPersonas[], int sizeArray);

#endif // FUNCIONES_H_INCLUDED

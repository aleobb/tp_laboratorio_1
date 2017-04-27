#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcionesAuxiliares.h"
#include "funciones.h"

#define EL_DATO_ES_VALIDO 1
#define EL_DATO_NO_ES_VALIDO 0
#define QTYPERSONA 20

/**
 * @brief Obtiene el primer indice libre del array.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tamaño del array se pasa como parametro.
 * @return devuelve el primer indice disponible (o -1 si no exite ninguno disponible)
 */
int obtenerEspacioLibre(EPersona arrayPersonas[], int sizeArray)
{
    int i;
    for (i=0; i<sizeArray; i++)
    {
        if (arrayPersonas[i].estado==-1)
            return i;
    }
    return -1;
}


/**
 * @brief Obtiene el indice que coincide con el dni pasado por parametro.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tamaño del array se pasa como parametro.
 * @param dni: a ser buscado en el array.
 * @return el indice en donde se encuentra el elemento que coincide con el parametro dni (o -1 si no lo encuentra)
 */
int buscarPorDni(EPersona arrayPersonas[], int sizeArray, long int dni)
{
    int i;
    for (i=0; i<sizeArray; i++)
        if ( arrayPersonas[i].dni==dni && arrayPersonas[i].estado==1 )
            return i;
    return -1;
}


/**
 * @brief Realiza el ingresdo de datos de una persona.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tamaño del array se pasa como parametro.
 * @return devuelve 1 (EL_DATO_ES_VALIDO) si el ingreso se pudo realizar correctamente.
 */
int ingresoPersona(EPersona arrayPersonas[],int sizeArray)
{
    int indice;
    int noDuplicado=0;
    char salir='n';
    EPersona arrayAuxiliar[1];

    indice=obtenerEspacioLibre(arrayPersonas,sizeArray);
    if (indice<0)
    {
        printf("\n No se puede agregar persona porque se agoto el espacio disponible! \n");
        salir='s';
    }
    while (salir!='s' && salir!='S')
    {
        arrayAuxiliar[0].dni=ingresoDNI();
        noDuplicado=buscarPorDni(arrayPersonas,sizeArray,arrayAuxiliar[0].dni);
        if (noDuplicado<0)
        {
            ingresoDatos(arrayAuxiliar);
            arrayPersonas[indice]=arrayAuxiliar[0];
            return EL_DATO_ES_VALIDO;
        }
        getString("\n El nro. de DNI ya se encuentra ingresado! \
            \n Ingrese 'S' para salir de la carga de datos o cualquier otra tecla para continuar: ",&salir);
    }
    return EL_DATO_NO_ES_VALIDO;
}




/**
 * @brief Realiza la modificacion de datos de una persona.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tamaño del array se pasa como parametro.
 * @return devuelve 1 (EL_DATO_ES_VALIDO) si la modificacion se pudo realizar correctamente.
 */
int modificacionPersona(EPersona arrayPersonas[], int sizeArray)
{
    int indice;
    char salir='n';
    EPersona arrayAuxiliar[1];

    while (salir!='s' && salir!='S')
    {
        arrayAuxiliar[0].dni=ingresoDNI();
        indice=buscarPorDni(arrayPersonas,sizeArray,arrayAuxiliar[0].dni);
        if (indice>=0)
        {
            ingresoDatos(arrayAuxiliar);
            arrayPersonas[indice]=arrayAuxiliar[0];
            return EL_DATO_ES_VALIDO;
        }
        getString("\n No se puede eliminar persona porque ese nro. de DNI no se encuentra cargado! \
            \n Ingrese 'S' para salir de la carga de datos o cualquier otra tecla para continuar: ",&salir);
    }
    return EL_DATO_NO_ES_VALIDO;
}




/**
 * @brief Realiza la baja logica del registro de datos de una persona.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tamaño del array se pasa como parametro.
 * @return devuelve 1 (EL_DATO_ES_VALIDO) si la baja se pudo realizar correctamente.
 */
int eliminarPersona(EPersona arrayPersonas[], int sizeArray)
{
    int indice;
    char salir='n';

    while (salir!='s' && salir!='S')
    {
        indice=buscarPorDni(arrayPersonas, sizeArray, ingresoDNI() );
        if (indice>=0)
        {
            arrayPersonas[indice].estado=-1;
            printf("\n El registro de datos de la persona correspondiente al DNI %ld ha sido borrado. \n", arrayPersonas[indice].dni);
            return EL_DATO_ES_VALIDO;
        }
        getString("\n El nro. de DNI no se encuentra ingresado! \
            \n Ingrese 'S' para salir o cualquier otra tecla para reintentar: ",&salir);
    }
    return EL_DATO_NO_ES_VALIDO;
}




long int ingresoDNI()
{
    long int dni;
    getLongInt(&dni, "\n Ingrese el DNI de la persona (sin puntos): ", "\n El dato ingresado es invalido!\
        \n El DNI debe ser un numero positvo entre 1 y 99.999.999",1,1,1,1,99999999);
    return dni;
}


void ingresoDatos(EPersona arrayAuxiliar[])
{
    char arrayCharsAdmitidos[2]=" '";

    getType("\n Ingrese el nombre de la persona: ", "\n El dato ingresado es invalido!\
        \n Solo se adminten letras, espacios y el caracter ['] \n",1,1,arrayCharsAdmitidos,50,arrayAuxiliar[0].nombre);
    getInt(&arrayAuxiliar[0].edad, "\n Ingrese la edad de la persona: ", "\n El dato ingresado es invalido!\
        \n La edad debe ser un numero positvo entre 0 y 150 \n",1,1,0,1,150);
    arrayAuxiliar[0].estado=1;

}


/**
 * @brief Realiza la inicializacion del arrayPersonas ingresando el valor -1 en el campo estado.
 * @param arrayPersonas el array se pasa como parametro.
 * @param sizeArray el tamaño del array se pasa como parametro.
 * @return no devuelve nada.
 */
void initArray(EPersona arrayPersonas[],int sizeArray)
{
    int i;
    for (i=0; i<sizeArray; i++)
        arrayPersonas[i].estado=-1;
}


void listarPorNombre(EPersona arrayPersonas[], int sizeArray)
{
    int i;
    for (i=0; i<sizeArray; i++)
        if (arrayPersonas[i].estado==1)
            printf("\n DNI %ld - Nombre: %s - Edad: %d - (Estado: %d - Indice: %d) ", arrayPersonas[i].dni, arrayPersonas[i].nombre, arrayPersonas[i].edad, arrayPersonas[i].estado, i);
    printf("\n");

}


void ordenarPorNombre(EPersona arrayPersonas[], int sizeArray)
{
    int i;
    int flagSwap = 1;
    EPersona aux;
    while(flagSwap)
    {
        flagSwap = 0;
        for(i = 0; i<sizeArray-1 ; i++)
        {
            if( stricmp(arrayPersonas[i].nombre,arrayPersonas[i+1].nombre) > 0 && arrayPersonas[i].estado==1)
            {
                aux = arrayPersonas[i];
                arrayPersonas[i] = arrayPersonas[i+1];
                arrayPersonas[i+1] = aux;
                flagSwap = 1;
            }
        }
    }
}


void graficoEdades(EPersona arrayPersonas[], int sizeArray)
{
    int i; /// variable auxiliar
    int edadMenorA19=0; /// contador de edades menores a 19
    int edadDesde19a35=0; /// contador de edades entre 19 y 35 (ambas inclusive)
    int edadMayorA35=0; /// contador edades mayores a 35
    int cantGrupoMasGrande; /// Con esta variable obtengo la altura maxima del grafico de barras

    /// defino variables de reemplazo para graficar cada grupo:
    char grupoMenorA19=' ';
    char grupo19a35=' ';
    char grupoMayorA35=' ';

    /// se recorre el array para obtener la cantidad de personas de cada grupo de edades:
    for(i=0;i<sizeArray;i++)
    {
        if(arrayPersonas[i].estado==1)
        {
            if(arrayPersonas[i].edad<19)
                edadMenorA19++;
            else if(arrayPersonas[i].edad>35)
                edadMayorA35++;
            else
                edadDesde19a35++;
        }
    }

    /// calculo cual es el grupo con mas personas:
    if(edadMenorA19 >= edadDesde19a35 && edadMenorA19 >= edadMayorA35)
        cantGrupoMasGrande=edadMenorA19;
    else if(edadDesde19a35 >= edadMenorA19 && edadDesde19a35 >= edadMayorA35)
        cantGrupoMasGrande=edadDesde19a35;
    else
        cantGrupoMasGrande=edadMayorA35;
    printf("\n\n");

    /// Con el codigo a continuacion genero el grafico con una cantidad de renglones maxima
    /// igual a la cantidad de personas del grupo de mayor cantidad de personas:
    /// (por ello se empieza a recorrer desde cantGrupoMasGrande hasta 1)
    for(i=cantGrupoMasGrande;i>0;i--)
    {
        if(i<=edadMenorA19 )
            grupoMenorA19='*';
        if(i<=edadDesde19a35)
            grupo19a35='*';
        if(i<=edadMayorA35)
            grupoMayorA35='*';
        printf("   %02d \t  %c \t  %c\t %c \t\n",i,grupoMenorA19,grupo19a35,grupoMayorA35);
    }
    printf("\n Grupo:\t <18\t19-35\t>35\n");
}




void cargaAutomatica(EPersona arrayPersonas[], int sizeArray)
{
    int i;
    int dni = 1;
///    char nombre[10]="nombre";
    int edad = dni*10;

    for (i=0; i<5; i++)
    {

        arrayPersonas[i].dni=dni;
        arrayPersonas[i].edad=edad;
        arrayPersonas[i].estado=1;

        dni++;
        edad = dni*10;
    }

    for ( ; i<10; i++)
    {

        arrayPersonas[i].dni=dni;
        arrayPersonas[i].edad=edad;
        arrayPersonas[i].estado=1;

        dni++;
        edad = dni-6;
    }


    strcpy(arrayPersonas[0].nombre,"BBB");
    strcpy(arrayPersonas[1].nombre,"AAA");
    strcpy(arrayPersonas[2].nombre,"CCC");
    strcpy(arrayPersonas[3].nombre,"EEE");
    strcpy(arrayPersonas[4].nombre,"DDD");
    strcpy(arrayPersonas[5].nombre,"RRR");
    strcpy(arrayPersonas[6].nombre,"PPP");
    strcpy(arrayPersonas[7].nombre,"ACE");
    strcpy(arrayPersonas[8].nombre,"Del");
    strcpy(arrayPersonas[9].nombre,"HUN");

    ///     printf("\n indice: %d",indice);
}







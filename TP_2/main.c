/********************************************************************************************
 *
 * Programa: Base de datos de Personas
 *
 * Objetivo:
 * Crear una base de datos de personas y poder listarla ordenadamente y graficarla.
 *
 * Version: 1.0 22 de Abril de 2017.
 * Autor: Ben Alejandro
 *
 ********************************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funciones.h"
#include "funcionesAuxiliares.h"

#define EL_DATO_ES_VALIDO 1
#define EL_DATO_NO_ES_VALIDO 0
#define QTYPERSONA 20  /// Cantidad de registros de personas a guardar


int main()
{
    EPersona arrayPersonas[QTYPERSONA];  /// Se crea el array donde se van a guardar los datos

    char seguir='s';
    int opcion=0;
    int contadorPersonas=0;

    initArray(arrayPersonas,QTYPERSONA); /// Se inicializa el array de personas

    while(seguir=='s')
    {
        printf("\n");
        printf("1- Agregar persona\n");
        printf("2- Borrar persona\n");
        printf("3- Imprimir lista ordenada por nombre\n");
        printf("4- Imprimir grafico de edades\n\n");
        printf("5- Salir\n");

        printf("\nIngrese una opcion: ");
        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                if ( ingresoPersona(arrayPersonas,QTYPERSONA) == EL_DATO_ES_VALIDO )
                    contadorPersonas++;
                break;
            case 2:
                if (contadorPersonas==0)
                    printf("\n No se puede eliminar persona porque no hay ningun dato cargado! \n");
                else
                    if ( eliminarPersona(arrayPersonas, QTYPERSONA) == EL_DATO_ES_VALIDO )
                        contadorPersonas--;
                break;
            case 3:
                if (contadorPersonas==0)
                    printf("\n Nada que listar! No hay ningun dato cargado. \n");
                else
                {
                    ordenarPorNombre(arrayPersonas, QTYPERSONA);
                    listarPorNombre(arrayPersonas, QTYPERSONA);
                }
                break;
            case 4:
                if (contadorPersonas==0)
                    printf("\n Nada que graficar! No hay ningun dato cargado. \n");
                else
                    graficoEdades(arrayPersonas, QTYPERSONA);
                break;
            case 5:
                seguir = 'n';
                break;
            default:
                printf("\n La opcion ingresada es invalida! Intente nuevamente. \n");
                break;
        }
    }

    return 0;
}

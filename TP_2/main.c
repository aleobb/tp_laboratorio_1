/********************************************************************************************
 * Programa: Trabajo Practico Nº 2
 *
 * Hacer un programa que defina un array de 20 ítems de esta estructura y con un menú como el
 * siguiente:
 * 1.Agregar una persona
 * 2.Borrar una persona
 * 3.Imprimir lista ordenada por nombre
 * 4.Imprimir gráfico de edades
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
#define QTYPERSONA 20


int main()
{
    EPersona arrayPersonas[QTYPERSONA];

    char seguir='s';
    int opcion=0;
    int contadorPersonas=0;

    initArray(arrayPersonas,QTYPERSONA);

    cargaAutomatica(arrayPersonas,QTYPERSONA);
    contadorPersonas=5;

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

                listarPorNombre(arrayPersonas, QTYPERSONA);
                printf("\n ");
                ordenarPorNombre(arrayPersonas, QTYPERSONA);
                printf("\n ");
                listarPorNombre(arrayPersonas, QTYPERSONA);
                break;
            case 4:
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
